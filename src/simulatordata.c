#define	__far
#define	_far
#define far

#include "kernel.h"

struct share_data	kernel_share_data;
struct share_data *kernel_share = &kernel_share_data;
