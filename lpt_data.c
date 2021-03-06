#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/io.h>

#define DRIVER_AUTHOR	"Alexei Bezborodov <AlexeiBv@yandex.ru>"
#define DRIVER_DESC		"A sample LPT driver"
#define DEVICE_NAME 	"lpt_data" // will be in /proc/devices  
#define PRINTK_PREFIX	"lpt_data: "

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE(DEVICE_NAME);

static const int s_VerMajor = 2653;
static int s_Device_Open = 0;
static unsigned char s_LastWriteData = 0;

static int device_open(struct inode *inode, struct file *file)
{
	if (s_Device_Open)
		return -EBUSY;
	s_Device_Open++; // ToDo: need Interlocked

	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	s_Device_Open--;
	
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file* a_Filp, char* a_Buffer, size_t a_Length, loff_t* a_Offset)
{	
	return snprintf(a_Buffer, a_Length, "Last write data: %x", s_LastWriteData);
}

static ssize_t device_write(struct file* a_Filp, const char* a_Buff, size_t a_Len, loff_t* a_Off)
{
	const int lpt_port = 0x378;
	
	int i = 0;
	for (i = 0; i < a_Len; i++)
	{
		char curValue = a_Buff[i];
		outb(curValue, lpt_port);
		s_LastWriteData = curValue;
	}
	
	return a_Len;
}

int init_module(void)
{
	static struct file_operations fops =
	{
		.read 		= device_read,
		.write 		= device_write,
		.open 		= device_open,
		.release 	= device_release
	};

	int ret = register_chrdev(s_VerMajor, DEVICE_NAME, &fops);

	if (ret != 0)
	{
		printk(PRINTK_PREFIX"Registering the character device failed with %d\n", ret);
		return ret;
	}
	
	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(s_VerMajor, DEVICE_NAME);
}
