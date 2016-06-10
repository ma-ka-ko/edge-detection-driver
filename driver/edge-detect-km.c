
#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


MODULE_AUTHOR("Oscar A Gomez");
MODULE_LICENSE("GPL v2");

#define MAX_JPEG_SIZE 1024*1024

static int edge_major = -1;
static int edge_minor = 0;
static char * edge_name = "edge";

char  buffer[MAX_JPEG_SIZE];
static ssize_t currentOff = -1;
static ssize_t imageSize = -1;


int edge_open(struct inode *inode, struct file *filp)
{
	printk("my edge open\n");
	if(currentOff > 0)
		currentOff = 0;
	return 0;
}


long edge_ioctl(struct file *filp, unsigned int iocmd, unsigned long arg)
{
	printk("my edge ioctl: %d \n", iocmd);
	return -ENOTTY;
}

ssize_t edge_read(struct file *filp, char __user *buf, size_t n, loff_t *fpos)
{
	size_t nsize = n;
	size_t not_written;

	printk("my edge read %lu \n", n);
	if(currentOff == -1)
	{
		printk("Nothing to read!!\n");
		return -ENOENT;
	}

	if(n + currentOff > imageSize)
		nsize = imageSize - currentOff;

	not_written = copy_to_user(buf, buffer + currentOff, nsize);
	if (not_written != 0 )
	{
		printk( "unable to send all info to user, missing %lu \n", not_written);
		currentOff += (nsize- not_written);
		return nsize - not_written;
	}
	currentOff += nsize;

	//printk("Buffer: %s",buffer);
	return nsize;
}


static ssize_t edge_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
	size_t not_read;
	printk("my edge write %lu \n", count);
	not_read = copy_from_user(buffer,buf,count);
	if (not_read != 0 )
	{
		printk( "unable to receive all info from user, missing %lu\n", not_read);
		return count - not_read;
	}
	//printk("Buffer: %s",buffer);
	currentOff = 0;
	return count;
}


int edge_release(struct inode *inode, struct file *filp)
{
	printk("my edge release \n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open  = edge_open,
	.read  = edge_read,
	.write = edge_write,
	.unlocked_ioctl = edge_ioctl,
	.release = edge_release,
};

static struct class *edge_class;

static int __init edge_init(void)
{
	printk(KERN_EMERG "Hallo driver ... \n" );

	memset(buffer,0,MAX_JPEG_SIZE);

	// get dynamic major num
	edge_major = register_chrdev(0,"edge",&fops);
	//result = register_chrdev_region(devno, 1, "edge");
	if (edge_major < 0 ) {
		printk( "unable to register device %d\n", edge_major);
		return edge_major;
	}

	edge_class = class_create(THIS_MODULE, "edge");
	device_create(edge_class, NULL,MKDEV(edge_major, edge_minor), NULL, edge_name);


	return 0;
}

static void __exit edge_exit(void)
{
	unregister_chrdev(edge_major,"edge");
	device_destroy(edge_class, MKDEV(edge_major, edge_minor));
	class_destroy(edge_class);
	printk(KERN_EMERG "Tschuss driver ... \n" );
}

module_init(edge_init);
module_exit(edge_exit);
