# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"

int main(){
	static char	*s[255];
	char		buf[100 + 1];
	char		*tmp;
	int			ret;
    int         fd = open("touch", O_RDWR);
    printf("%d\n", fd);
	if (fd < 0)
		return (-1);
	ret = read(fd, buf, 100);
	if (ret < 0)
		return (-1);
}
