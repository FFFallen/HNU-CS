#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main (int argc, char *argv[])
{
  int fd = open(argv[1], O_RDWR);		//打开目标文件，打开方式为可读可写
  struct stat sb;
  size_t length;
  if (fd == -1)											//文件打开失败
  {
    perror("open");
    exit(1);
  }
	if (fstat(fd, &sb) == -1)					//获取文件状态
  {
    perror ("fstat");
    exit(1);
  }
  length = sb.st_size;							//获取文件长度（大小）
  
  //void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
  //addr:指定映射的起始地址，通常设为NULL，由内核来分配，映射成功后，return 该地址
  //length：代表将文件中映射到内存的部分的长度，单位为字节数，一般要求为页大小整数倍
  /*prot：映射区域的保护方式。可以为以下几种方式的组合：
  	PROT_EXEC 映射区域可被执行
		PROT_READ 映射区域可被读取
		PROT_WRITE 映射区域可被写入
		PROT_NONE 映射区域不能存取
	*/
  /*flags：影响映射区域的各种特性。在调用mmap()时必须要指定MAP_SHARED 或MAP_PRIVATE
  	MAP_FIXED 如果参数start所指的地址无法成功建立映射时，则放弃映射，不对地址做修正.
		MAP_SHARED对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享.
		MAP_PRIVATE 对映射区域的写入操作会产生一个映射文件的复制，即私人的“写入时复制”（copy on write）对此区域作的任何修改都不会写回原来的文件内容.
 	*/
  //fd：要映射到内存中的文件描述符，即调用mmap前调用open函数的返回值。（如果使用匿名内存映射时，即flags中设置了MAP_ANONYMOUS，fd设为-1。）
  //offset：文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。
    char *addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED)
  {
    perror ("mmap");
    exit(1);
  }
  
  //修改内存映射区域的内容
  char *p = strchr(addr, 'H');		//查找'H'字符的位置
  *p = 'J';												//将'H'替换成'J"
  
  if (munmap(addr, length) == -1)	//解除内存映射
  {
    perror ("munmap");
    exit(1);
  }
  
  close(fd);
  
  return 0;
}
