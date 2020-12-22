// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>

#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

struct list_item {
	struct list_head next;
	ktime_t start_time;
	ktime_t finish_time;
};

MODULE_AUTHOR("Jack Shendrikov <jackshen@ukr.net>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("3.0");

static LIST_HEAD(head);

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Count to print 'Hello, world!'");

static int __init hello_init(void)
{
	uint i = 0;
	struct list_item *tail;

	pr_info("Count: %d\n", count);

	if (!count)
		pr_warn("The parameter is 0. You cannot enter 0.");

	if (count >= 5 && count <= 10)
		pr_warn("The parameter is %d, between [5;10], enter number less than 5", count);

	BUG_ON(count > 10);

	for (i = 0; i < count; i++) {
		tail = kmalloc(sizeof(struct list_item), GFP_KERNEL);

		if (i == 5)
			tail = 0;

		if (ZERO_OR_NULL_PTR(tail))
			goto error;

		tail->start_time = ktime_get();
		pr_info("Hello, World!\n");
		tail->finish_time = ktime_get();

		list_add_tail(&(tail->next), &head);
	}

	return 0;

error:
	{
		struct list_item *md, *tmp;

		pr_err("Out of memory!\n");

		list_for_each_entry_safe(md, tmp, &head, next) {
			list_del(&md->next);
			kfree(md);
		}

		BUG();
		return -ENOMEM;
	}
}


static void __exit hello_exit(void)
{
	struct list_item *md, *tmp;

	list_for_each_entry_safe(md, tmp, &head, next) {
		pr_info("Printing time: %lld",
		md->finish_time - md->start_time);

		list_del(&md->next);
		kfree(md);
	}

	BUG_ON(!list_empty(&head));
}

module_init(hello_init);
module_exit(hello_exit);