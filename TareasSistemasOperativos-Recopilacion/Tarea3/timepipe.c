#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#define MSGSIZE 7

int main(int argc , char *argv[] ){




        pid_t pid;
        int status;
        struct timeval startTime;
        struct timeval endTime;
	char inMsg[MSGSIZE];
	int p[2], nbytes;
	char outMsg[MSGSIZE];

	if(pipe(p) < 0){
		printf("Valor del errno: %d\n", errno);
		fprintf(stderr, "No se puedo crear el pipe, el error es: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	};
        
	
	pid = fork();

        if (pid == -1){
                printf("No se pudo hacer fork, intente de nuevo");
                exit(EXIT_FAILURE);
        }


        if(pid == 0){

                int i;
                char *argv_list[30] = {};
                
 		for( i = 1; i < argc; i++){
                        argv_list[i-1]=argv[i];
                   }

                argv_list[argc]= NULL;
                gettimeofday(&startTime,NULL);
		snprintf(outMsg,sizeof(outMsg),"%ld",startTime.tv_usec);
		int writedBytes = write(p[1], outMsg, MSGSIZE);
                if(writedBytes == -1){
			printf("Valor del errno: %d\n", errno);
			fprintf(stderr, "No se pudo escribir en el pipe, el error es: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		execvp(argv[1], argv_list);
		               
	}

        else{
                if (waitpid(pid, &status, 0) > 0){
                gettimeofday(&endTime,NULL);
               
		
		if((nbytes = read(p[0], inMsg, MSGSIZE)) > 0 ){
		
			char* temp;
			long tiempo_inicial = strtol((char*)inMsg,&temp,10);
                        printf("Elapsed time: %ld microseconds\n", (endTime.tv_usec - tiempo_inicial));

		}

		if(nbytes == -1){
			printf("Valor del errno: %d\n", errno);
			fprintf(stderr, "No se puedo leer desde el pipe, el error es: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	
                printf("Ejecucion Terminada Exitosamente\n");
		exit(0);
                }
                else
                printf("Hubo un fallo con el waitpid\n");


        }

        exit(0);
}


