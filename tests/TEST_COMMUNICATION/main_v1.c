#include "stream.h"
int ports1 = 5000;
int ports2 = 5001;
int ports3 = 5002;
int portc1 = 5003;
int portc2 = 5006;
int portc3 = 5009;
int fermer = 0;
int fping = 0;
int pid_p = 0;
//int nbfils = 0;
void* client(void *);
void* serveur(void *);

void derouter(int sig){
	int status;
	int pid = wait(&status);
	printf("Le processus PID = %d vient de se terminer avec le statut %d \n",pid,status);
	//nbfils--;
}

int main(){
	char buffer[10] = "";
	pthread_t th[3];
	void** resTh;

	
	int i=0;
	int pid;
	pid_p = getpid();
  
	TEST  (( pid = fork()) , "ERREUR CREATION SERVEUR" );
  
    if (pid == 0){
	pid_p = getpid();	
		// insérer ici threads serveur + delete le reste inutile
		printf("%d : serveur lance \n",pid_p);

	  //partie serveur
	
		printf("%d : Creation thead 1 : 1er serveur \n",pid_p);
		TEST(pthread_create(&th[0],NULL,serveur,(void*)&ports1),"ERREUR CREATION THREAD CLIENT1")
		printf("%d : Creation thead 2 : 2eme serveur \n",pid_p);
		TEST(pthread_create(&th[1],NULL,serveur,(void*)&ports2),"ERREUR CREATION THREAD CLIENT2")
		printf("%d : Creation thead 3 : 3eme serveur \n",pid_p);
		TEST(pthread_create(&th[2],NULL,serveur,(void*)&ports3),"ERREUR CREATION THREAD CLIENT3")
		
		
		
		pthread_join(th[0],NULL);
		pthread_join(th[1],NULL);
		pthread_join(th[2], NULL);
	  
	  //while(1){
	  //	if(nbfils == 0){
		exit(0);
		}

 
 // partie client
  sleep(20);
		printf("%d : Creation thead 1 : 1er client \n",pid_p);
		TEST(pthread_create(&th[0],NULL,client,(void*)&portc1),"ERREUR CREATION THREAD CLIENT1")
		printf("%d : Creation thead 2 : 2eme client \n",pid_p);
		TEST(pthread_create(&th[1],NULL,client,(void*)&portc2),"ERREUR CREATION THREAD CLIENT2")
		printf("%d : Creation thead 3 : 3eme client \n",pid_p);
		TEST(pthread_create(&th[2],NULL,client,(void*)&portc3),"ERREUR CREATION THREAD CLIENT3")
		
		sleep(20);
		while(fermer != 1){
			printf("Ping ?\n");
			scanf("%s",buffer);
			if(strcmp(buffer,"ping") == 0){
				fping = 1;
				strcpy(buffer , "");
			}
			if(strcmp(buffer,"quit") == 0){
				fermer = 1;
			}
		}

		

		pthread_join(th[0],NULL);
		pthread_join(th[1],NULL);
		pthread_join(th[2], NULL);

		
		sleep(20);
  return 0; }
  
  
void* client(void * arg){
		int* myArg = (int*)arg;
		char buffer[BUFF_MAX] = "";
		int c;
		c = socket ( AF_INET, SOCK_STREAM, 0 );
		struct sockaddr_in as;
		as.sin_family = AF_INET;
		as.sin_port = htons(*myArg);
		inet_aton("127.0.0.1",&(as.sin_addr));
		memset ( as.sin_zero, 0, 8 );
		
		printf("Tentative connexion Socket port %d \n",*myArg);
		
		TEST ( connect ( c, ( struct sockaddr * ) &as, sizeof ( as ) ), "ERREUR" );

		printf("Socket port %d connectee \n",*myArg);
		sleep(5);
		while(fermer != 1){
			if (fping == 1){
				TEST ( write ( c, "ping", 4 ), "ERREUR" );
				fping = 0 ;
				TEST ( read ( c, &buffer, BUFF_MAX ), "ERREUR" );
				printf("read effectué \n"); 
				if ( strcmp("pong",buffer) == 0 )
					printf("pong reçu \n");
				else
					printf("Pong pas reçu \n");
			}
			
		}
		sleep(10);
		close ( c );
		
	pthread_exit(0);
}

void* serveur(void * arg){
	int* myArg = (int*)arg;
	  //partie serveur	

		//création de serveur (socket ecoute)
		char bufferRead[10] = "";
		int sa;
		sa = socket ( AF_INET, SOCK_STREAM, 0 );
		struct sockaddr_in as;
		as.sin_family = AF_INET;
		as.sin_port = htons ( *myArg );
		inet_aton ( "127.0.0.1", &( as.sin_addr ) );
		memset ( as.sin_zero, 0, 8 );
		TEST ( bind ( sa, ( struct sockaddr * ) &as, sizeof ( as ) ), "ERREUR" )
		TEST ( listen ( sa, 1 ), "ERREUR" )

		struct sigaction newAct;
		newAct.sa_handler  = derouter;
		newAct.sa_flags = SA_RESTART;
		TEST ( sigemptyset(&newAct.sa_mask), "ERREUR");
		TEST ( sigaction(SIGCHLD,&newAct,NULL), "ERREUR");
		int sd;
		struct sockaddr_in ac;
		socklen_t taille = sizeof ( ac );
		
		
		printf("%d : serveur en attente de conexion sur port %d \n",pid_p,*myArg);
		TEST ( ( sd = accept ( sa, ( struct sockaddr * ) &ac, &taille ) ), "ERREUR" );
		//printf ( "Adresse %s\n", inet_ntoa ( ac.sin_addr ) );
		printf("%d : connexion acceptee \n",pid_p);
		

		printf("%d : TRAITEMENT socket port %d : \n",pid_p,*myArg);
		while(1){
			TEST ( read ( sd, bufferRead, 10 ), "ERREUR" );
			printf("%d : read effectué \n",pid_p);
			if(strcmp(bufferRead,"ping")==0){
				printf("%d : ping recu \n",pid_p);
				TEST ( write ( sd, "pong", 4 ), "ERREUR" );
				printf("%d : pong effectué \n",pid_p);
			}
			else{
				printf("%d : QQCH recu \n",pid_p);
				TEST ( write ( sd, "Pas compris", 11 ), "ERREUR" );
				printf("%d : envoie un pas compris \n",pid_p);
			}
			if(fermer == 1){
					close ( sa );
					close(sd);
					pthread_exit(0);
			}
		}
}