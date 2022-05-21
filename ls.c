


#include "minishell.h"


// struct dirent {
//   ino_t          d_ino;       /* inode number */
//   off_t          d_off;       /* offset to the next dirent */
//   unsigned short d_reclen;    /* length of this record */
//   unsigned char  d_type;      /* type of file; not supported
//                                  by all file system types */
//   char           d_name[256]; /* filename */
// };


void    ls(char *str, char *envp[])
{
    DIR             *dir;
    struct dirent   *rd;

    dir = opendir(".");
    if (!dir)
    {
        perror("minishell");
        return ;
    }
    rd = readdir(dir);
    
    while ((rd = readdir(dir)) != NULL)
    {
        printf ("%s\t", rd->d_name);
    }
    printf ("\n");
}