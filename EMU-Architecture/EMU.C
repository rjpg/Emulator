#include <stdio.h>
#include <string.h>
#include <stdlib.h>

short int REGISTERS[10];

unsigned int PROGRAM[65536];
short int MEMORY[65536];

unsigned short int PROGAMCOUNT;
int EXECUTING=0;
int ciclos;

short int STACK[256];
short int POIT_STACK;


#define  R1 REGISTERS[0]
#define  R2 REGISTERS[1]
#define  R3 REGISTERS[2]
#define  R4 REGISTERS[3]
#define  R5 REGISTERS[4]
#define  R6 REGISTERS[5]
#define  R7 REGISTERS[6]
#define  R8 REGISTERS[7]
#define  R9 REGISTERS[8]
#define  R10 REGISTERS[9]


short int N_execucoes[0x24];

void add (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] +
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=1;
        
}

void sub (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] -
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=1;
}

void mul (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] *
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=2;
}

void dif (int param)   // "dif" era para ser "div" ... por causa do stdlib
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] /
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=3;
}

void not (int param)
{
        REGISTERS[param & 0x0000000F]=
        !REGISTERS[ (param>>4) & 0x0000000F];
        ciclos+=1;        
}

void and (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] &
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=1;        
}

void or (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] |
        REGISTERS[ (param>>8) & 0x0000000F];
        ciclos+=1;        
}

void sl (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] <<
        ((param>>8) & 0x0000FFFF);
        ciclos+=2;
                
}

void sr (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] <<
        ((param>>8) & 0x0000FFFF);
        ciclos+=2;
               
}

void lw (int param)
{
        REGISTERS[param & 0x0000000F]=
        MEMORY[ ((param>>8) & 0x0000FFFF) +
        REGISTERS[ (param>>4) & 0x0000000F]];
        ciclos+=8;
}


void sw (int param)
{
        MEMORY[((param>>8) & 0x0000FFFF) +
        REGISTERS[ (param>>4) & 0x0000000F]] =
        REGISTERS[param & 0x0000000F];
        ciclos+=6;
}

void j (int param)
{
        PROGAMCOUNT=((param>>8) & 0x0000FFFF);
        ciclos+=7;
}

void jr(int param)
{
        PROGAMCOUNT=REGISTERS[param & 0x0000000F];
        ciclos+=7;
}

void br(int param)
{
        PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=7;
}

void beq(int param)
{
        if ( REGISTERS[param & 0x0000000F] ==
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;
}

void bne(int param)
{
        if ( REGISTERS[param & 0x0000000F] !=
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;        
}

void bgt(int param)
{
        if ( REGISTERS[param & 0x0000000F] >
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;        
}

void bge(int param)
{
        if ( REGISTERS[param & 0x0000000F] >=
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;        
}

void blt(int param)
{
        if ( REGISTERS[param & 0x0000000F] <
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;                                 
}


void ble(int param)
{
        if ( REGISTERS[param & 0x0000000F] <=
                REGISTERS[ (param>>4) & 0x0000000F])
                PROGAMCOUNT=(param>>8) & 0x0000FFFF;
        ciclos+=8;        
}


void seq (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] ==
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void sne (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] !=
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void sgt (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] >
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void sge (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] >=
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void slt (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] <
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void sle (int param)
{
        if (REGISTERS[ (param>>4) & 0x0000000F] <=
        REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]= 1;
        else
                REGISTERS[param & 0x0000000F]= 0;
        ciclos+=1;
}

void addi (int param)
{
        REGISTERS[param & 0x0000000F]=
        REGISTERS[ (param>>4) & 0x0000000F] +
        ((param>>8) & 0x0000FFFF);
        ciclos+=1;
}

void cset (int param)
{
        if (REGISTERS[ (param>>8) & 0x0000000F])
                REGISTERS[param & 0x0000000F]=
                REGISTERS[ (param>>4) & 0x0000000F];
        ciclos+=2;
}

void sys (int param)
{
        short int i;
        switch ( (param>>8) & 0x0000FFFF)
        {
                case 0x0000 : EXECUTING=0;printf("\nProgram STOP\n\n"); break;
                case 0x0001 : for (i=0;i<10;i++)
                                printf("R%d=%X ",i+1,REGISTERS[i]);
                              printf("\n");
                        break;
                case 0x0002 : printf ("R%d=%X\n",(param & 0x0000000F)+1,
                        REGISTERS[ param & 0x0000000F]);
                        break;
                case 0x0003 : printf("R%d:",(param & 0x0000000F)+1);
                        scanf ("%d",&i); //DEU TRABALHO ADVINHAR ESTA PARTE !!
                        REGISTERS[param & 0x0000000F]=(short int) i;
                        break;
                case 0x0004 :  break;
                case 0x0005 : break;
                case 0x0006 :  break;
                case 0x0009 : break;

        }

        ciclos+=10;
}

void pus (int param)
{
        STACK[POIT_STACK]=REGISTERS[ param & 0x0000000F];
        POIT_STACK++;
        ciclos+=3;
}

void pop (int param)
{
        REGISTERS[ param & 0x0000000F]=STACK[POIT_STACK-1];
        POIT_STACK--;
        ciclos+=3;
}

void pusaux (int param)
{
        STACK[POIT_STACK]=REGISTERS[ param & 0x0000000F];
        POIT_STACK++;
//        ciclos+=3;
}

void popaux (int param)
{
        REGISTERS[ param & 0x0000000F]=STACK[POIT_STACK-1];
        POIT_STACK--;
//        ciclos+=3;
}

void pua (void)
{
        int i;
        for (i=0;i<10;i++)
                pusaux (i);
        ciclos+=4;
}

void poa (void)
{
        int i;
        for (i=9;i>=-1;i--)
                popaux (i);
        ciclos+=4;
}


void puc (void)
{
        STACK[POIT_STACK]=PROGAMCOUNT;
        POIT_STACK++;
        ciclos+=3;
}

void poc (void)
{
        PROGAMCOUNT=STACK[POIT_STACK-1];
        POIT_STACK--;
        ciclos+=3;    
}

int execute (int inst)
{
        
        switch (inst & 0x000000FF)
        {
                case 0x00 : break;
                case 0x01 : add (inst>>8); break;
                case 0x02 : sub (inst>>8);break;
                case 0x03 : mul (inst>>8);break;
                case 0x04 : dif (inst>>8);break; // "dif" era para ser "div" ... por causa do stdlib
                case 0x05 : not (inst>>8); break;
                case 0x06 : and (inst>>8);break;
                case 0x07 : or (inst>>8);break;
                case 0x08 : sl (inst>>8);break;
                case 0x09 : sr (inst>>8);break;
                case 0x0A : lw (inst>>8);break;
                case 0x0B : sw (inst>>8);break;
                case 0x0C : j (inst>>8);break;
                case 0x0D : jr (inst>>8);break;
                case 0x0E : br (inst>>8);break;
                case 0x0F : beq (inst>>8);break;
                case 0x10 : bne (inst>>8);break;
                case 0x11 : bgt (inst>>8);break;
                case 0x12 : bge (inst>>8);break;
                case 0x13 : blt (inst>>8);break;
                case 0x14 : ble (inst>>8);break;
                case 0x15 : seq (inst>>8);break;
                case 0x16 : sne (inst>>8);break;
                case 0x17 : sgt (inst>>8);break;
                case 0x18 : sge (inst>>8);break;
                case 0x19 : slt (inst>>8);break;
                case 0x1A : sle (inst>>8);break;
                case 0x1B : addi (inst>>8);break;
                case 0x1C : cset (inst>>8);break;
                case 0x1D : sys (inst>>8);break;
                case 0x1E : pus (inst>>8);break;
                case 0x1F : pop (inst>>8);break;
                case 0x20 : pua ();break;
                case 0x21 : poa ();break;
                case 0x22 : puc ();break;
                case 0x23 : poc ();break;
                default   : printf("Error : Unknone instruction [PC:%d]\n",PROGAMCOUNT);
                        exit (1);
        }
        N_execucoes[inst & 0x000000FF]++;
return 0;
}

/*
main()
{
        
        int a=0xFFFFFFFF;
        R1=26;


        printf ("%X\n",a);
        printf ("-----------------\n");
        R4 = 0;
        R2 = 4;
        R3 = 2;
        printf ("R4=%X\n",R4);
        printf ("R2=%X\n",R2);
        printf ("R3=%X\n",R3);
        execute(0x00021302);
        printf ("execute(0x00021302);\n");
        printf ("inst:0x02    - instru�ao SUB\n");
        printf ("par1:0x3     - registro 4\n");
        printf ("par2:0x1     - registro 2\n");
        printf ("par3:0x0002  - registro 3\n");
        printf ("   --  SUB R4 R2 R3 --\n");
        printf ("R4=%X\n",R4);
        printf ("-----------------\n");
        printf ("-----------------\n");
        printf ("execute(0x0000001D);\n");
        printf ("inst:0x1D    - instru�ao SYS\n");
        printf ("par3:0x0000  - 0=stop cpu \n");
        printf ("   --  SYS 0        --\n");
        PROGRAM[0]=0x0000001D;
        execute(PROGRAM[0]);
        printf ("-----------------\n");
        printf ("-----------------\n");
        printf ("teste de execu�ao de uma instruc�ao desconhecida\n");
        printf ("execute(0x0000002D);\n");
        execute(0x0000002D);
        printf ("-----------------\n");


        PROGRAM[0]=0xFFFFFFFF;
        REGISTERS[1]=0x1A0F;
        printf("%X\n",R2);
        printf("%X\n",PROGRAM[0]);
        printf("%d\n",sizeof(short int));

        
        PROGRAM[0]=0x0000001D;



        return 0;
} 
*/

void reset (void)
{
        int i;
        for (i=0;i<10;i++)
                REGISTERS[i]=0x0000;
        for (i=0;i<65536;i++)
                PROGRAM[i]=0x00000000;
        for (i=0;i<65536;i++)
                MEMORY[i]=0x0000;
        for (i=0;i<256;i++)
                STACK[i]=0;
        PROGAMCOUNT=0x0000;
        POIT_STACK=0x0000;
        ciclos=0;
        for (i=0;i<0x24;i++)
                N_execucoes[i]=0;


}

void print_state (void)
{
        int i;
        printf("----------- State Program -----------\n");
        printf ("Program_counter : %X\n",PROGAMCOUNT);
        printf ("Instru��o       : %X\n",PROGRAM[PROGAMCOUNT]);
        for (i=0;i<10;i++)
                printf("R%d=%X ",i+1,REGISTERS[i]);
        printf("\n-------------------------------------\n");
}

void show_mem (short int h)
{
        int i;
        int x=0;
        for (i=0;i<h;i++)
                {
                printf ("mem[%d]=%d ",i,MEMORY[i]);
                if (x++==5) {printf ("\n");x=0;}
                }
         printf ("\n");

}

void show_ins_table(void)
{
        int i;
        for (i=0;i<0x24;i++)
                if (N_execucoes[i]!=0)
                printf("ins 0x%X used %d times\n",i,N_execucoes[i]);

        printf("\n");
}
main (int argc,char *argv[])
{
        int i,debug,x;
        FILE *in;
        char *file;

       printf ("\n(c) X-prog 2000  (Trabalho de A.C.) Emulador\n");

       if (argc<2)
                {
                printf ("\nNedeed 1 argument\n");
                printf ("Sintaxe: Xcompile [file in] [op]\n");
                printf ("EX:      Xcompile teste.xsm\n\n");
                printf ("op: -c     : N� ciclos\n");
                printf ("    -i     : N� execution of instruction\n");
                printf ("    -p     :  Estatistics\n");
                printf ("    -d     : Debugging\n");
                printf ("    -m ??? : Print memory\n");
                return 1;
                }

       debug=0;
       for (i=1;i<argc;i++)
                if (strcmp(argv[i],"-d")==0)
                        debug=1;


       file=argv[1];

       reset();

       printf ("Reading %s ...",file);
       
       if ((in = fopen(file, "rt"))== NULL)
       {
       printf("Error reading file\n");
       return 1;
       }

       i=0;
       x=0;
       while (EOF!=x) 
       {
          if (!(x=fscanf(in,"%X",&PROGRAM[i])))
                {
                printf("Error :Reading instruction [INST. n�:%d]\n",i);
                exit (1);
                }
          i++;
       }
       fclose (in);
       printf ("  Done.\n\n");
       print_state();
       EXECUTING=1;
       while (EXECUTING==1)
       {
                execute(PROGRAM[PROGAMCOUNT++]);
                if (debug!=0) {print_state();x=getchar();}
       }

       for (i=1;i<argc;i++)
                if (strcmp(argv[i],"-c")==0)
                       printf ("tempo (ciclos) : %d\n\n",ciclos);

       for (i=1;i<argc;i++)
                if (strcmp(argv[i],"-i")==0)
                        show_ins_table();

       for (i=1;i<argc;i++)
                if (strcmp(argv[i],"-m")==0)
                        {
                        sscanf(argv[i+1],"%d",&x);
                        show_mem(x);
                        }
 

       return 0;
}




