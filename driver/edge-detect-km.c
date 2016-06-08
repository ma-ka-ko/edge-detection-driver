
#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


MODULE_AUTHOR("Oscar A Gomez");
MODULE_LICENSE("GPL v2");

//static dev_t devno = MKDEV(233,0);
int edge_major = -1;
int edge_minor = 0;
char * edge_name = "edge";


int edge_open(struct inode *inode, struct file *filp)
{
	printk("my edge open\n");
	return 0;
}

long edge_ioctl(struct file *filp, unsigned int iocmd, unsigned long arg)
{
	printk("my edge close\n");
	return -ENOTTY;
}

ssize_t edge_read(struct file *filp, char __user *buf, size_t n, loff_t *fpos)
{
	char mbuf[] = {'a','b','c','d'};

	copy_to_user(buf, mbuf, 4);
	return 4;
}


static ssize_t edge_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
	return count;
}


int edge_release(struct inode *inode, struct file *filp)
{
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
