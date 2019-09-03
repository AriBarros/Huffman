#include <stdlib.h>
#include <stdio.h>
#include "zip.h"
#include "unzip.h"

int main()
{
   int op;
  
   do{
		
        printf("\n--------Menu--------\n\n1 - Compress file\n2 - Decompress file\n3 - Exit\n--------------------\nOption:"); 
        scanf("%d", &op);
        getchar();
        if(op == 1){
            printf(" Welcome to File Compression of Operators!\n");
            zip_file();
        }
        else if(op == 2){
            printf(" Welcome to the decompression of Operators files!\n");
            unzip_file();
        }
		else if(op == 3)
		{
			printf("Exit!\n");
		}
    } while(op!= 3 );
    return 0;
}
