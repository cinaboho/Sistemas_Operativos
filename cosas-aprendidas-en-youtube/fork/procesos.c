/* -------------------------------------------------------------------------- */
/*                     Creacion de procesos padre e hijos                     */
/* -------------------------------------------------------------------------- */
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pidC;
    int var=2;

    printf("** proc. PID = %d comienza ** \n", getpid());
    pidC = fork();
    printf("proc. PID = %d , pidC = %d ejecutandose \n", getpid(),pidC);
    if(pidC>0){ //Se esta ejecutando el padre
        printf("Padre\n");
        var =44;
    }
    else if(pidC == 0){ //Se esta ejecutando el hijo
        printf("Hijo\n");
        var = 33;
    }
    else{
        //error
    }
    while(1){
        sleep(2);
    printf("proc. PID = %d , var = %d ejecutandose \n", getpid(),var);
    }
    return 0;
}
