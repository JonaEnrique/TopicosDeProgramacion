#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *pArch = fopen("prueba.dat", "wb");
    int entero = 0;

    while(entero < 10)
    {
        printf("%p %d %d %d %d %d %p %p\n", pArch->_base,
                                      pArch->_bufsiz,
                                      pArch->_charbuf,
                                      pArch->_cnt,
                                      pArch->_file,
                                      pArch->_flag,
                                      pArch->_ptr,
                                      pArch->_tmpfname);

        fwrite(&entero, sizeof(int), 1, pArch);

        entero++;
    }

    printf("%p %d %d %d %d %d %p %p\n", pArch->_base,
                                      pArch->_bufsiz,
                                      pArch->_charbuf,
                                      pArch->_cnt,
                                      pArch->_file,
                                      pArch->_flag,
                                      pArch->_ptr,
                                      pArch->_tmpfname);

    return 0;
}
