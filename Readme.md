Merci a Antoine Boisvert(André Barnet) pour le programme de debug C_tools. Pratique pour faire
imprimer les characters ascii non imprimable.
================================================================================

https://www.rfc-editor.org/rfc/rfc1459
https://www.alien.net.au/irc/irc2numerics.html

exchat client
brew install --cask wechat




socket()
=================

La fonction socket() en C est utilisée pour créer une nouvelle socket, qui est un point de terminaison pour la communication réseau. La fonction prend trois arguments :


int socket(int domain, int type, int protocol);

    domain : le domaine de communication, comme AF_INET (IPv4) ou AF_INET6 (IPv6) pour les communications Internet
    type : le type de socket, comme SOCK_STREAM (pour TCP) ou SOCK_DGRAM (pour UDP)
    protocol : le protocole utilisé pour la communication, comme IPPROTO_TCP (pour TCP) ou IPPROTO_UDP (pour UDP)

Voici un exemple de code pour créer une nouvelle socket en utilisant la fonction socket() :

#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("Erreur lors de la création de la socket");
        return 1;
    }

    // Utiliser la socket...

    close(sockfd);
    return 0;
}

Dans cet exemple, nous créons une nouvelle socket en utilisant le domaine de communication AF_INET, le type de socket SOCK_STREAM (pour TCP) et le protocole 0 (qui permet de choisir automatiquement le protocole approprié). Si la fonction socket() échoue, nous affichons un message d'erreur en utilisant la fonction perror(). Ensuite, nous pouvons utiliser la socket pour la communication, et finalement, nous la fermons en utilisant la fonction close().

---------------------------------------------------------------------------

setsockopt()
=================

La fonction setsockopt() en C est utilisée pour définir les options de socket. Elle permet de définir des paramètres de communication pour une socket ou un canal de communication.

Voici la syntaxe de la fonction :


int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

    sockfd : l'identifiant de la socket
    level : le niveau auquel l'option est définie, généralement SOL_SOCKET
    optname : l'option que l'on souhaite définir
    optval : la valeur de l'option
    optlen : la longueur de la valeur de l'option

Voici un exemple de code pour utiliser la fonction setsockopt() pour définir le temps de déconnexion maximum d'une socket :


#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Définir le temps de déconnexion maximum de la socket à 30 secondes
    int timeout = 30;
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // Utiliser la socket...

    close(sockfd);
    return 0;
}

Dans cet exemple, nous définissons le temps de déconnexion maximum de la socket à 30 secondes en utilisant l'option SO_RCVTIMEO. La structure timeval est utilisée pour définir le temps d'attente, et nous appelons la fonction setsockopt() pour appliquer cette option à notre socket.

---------------------------------------------------------------------------

Getsockname()
=================

La fonction getsockname() en C est utilisée pour obtenir l'adresse locale et le numéro de port d'une socket. Cette fonction est souvent utilisée pour récupérer l'adresse IP et le port utilisés par une socket qui a été créée avec un numéro de port aléatoire, par exemple.

Voici la syntaxe de la fonction :

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    sockfd : l'identifiant de la socket pour laquelle on souhaite obtenir l'adresse
    addr : un pointeur vers une structure sockaddr qui sera remplie avec l'adresse
    addrlen : un pointeur vers une variable contenant la longueur de la structure sockaddr

Voici un exemple de code pour utiliser la fonction getsockname() pour obtenir l'adresse IP et le port d'une socket :

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Connecter la socket à une adresse et un port
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Adresse IP locale (127.0.0.1)
    serv_addr.sin_port = htons(8080); // Numéro de port 8080
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Obtenir l'adresse IP et le port de la socket
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    getsockname(sockfd, (struct sockaddr *)&addr, &addrlen);
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ip_str, INET_ADDRSTRLEN);
    printf("Adresse IP : %s\n", ip_str);
    printf("Port : %d\n", ntohs(addr.sin_port));

    close(sockfd);
    return 0;
}

Dans cet exemple, nous créons une nouvelle socket en utilisant le domaine de communication AF_INET, le type de socket SOCK_STREAM (pour TCP) et le protocole 0 (qui permet de choisir automatiquement le protocole approprié). Ensuite, nous connectons la socket à une adresse et un port spécifiques en utilisant la fonction connect(). Enfin, nous utilisons la fonction getsockname() pour obtenir l'adresse IP et le port de la socket, que nous affichons à l'aide de la fonction printf(). Notez que nous utilisons les fonctions htons() et ntohs() pour convertir les numéros de port entre le format réseau et le format hôte.

---------------------------------------------------------------------------

getprotobyname()
=================

La fonction getprotobyname() en C est utilisée pour obtenir les informations sur un protocole réseau à partir de son nom. Elle est souvent utilisée pour obtenir le numéro de protocole associé à un protocole donné.

Voici la syntaxe de la fonction :

struct protoent *getprotobyname(const char *name);

    name : le nom du protocole réseau que l'on souhaite rechercher

La fonction renvoie un pointeur vers une structure protoent qui contient des informations sur le protocole, telles que son nom, son numéro de protocole, et la famille de protocoles à laquelle il appartient.

Voici un exemple de code pour utiliser la fonction getprotobyname() pour obtenir les informations sur le protocole TCP :

#include <netdb.h>
#include <stdio.h>

int main()
{
    struct protoent *tcp = getprotobyname("tcp");

    if (tcp == NULL) {
        perror("Erreur lors de la recherche du protocole");
        return 1;
    }

    printf("Nom du protocole : %s\n", tcp->p_name);
    printf("Numéro de protocole : %d\n", tcp->p_proto);
    printf("Famille de protocoles : %d\n", tcp->p_family);

    return 0;
}

Dans cet exemple, nous utilisons la fonction getprotobyname() pour obtenir les informations sur le protocole TCP. Si la fonction renvoie NULL, nous affichons un message d'erreur en utilisant la fonction perror(). Sinon, nous affichons le nom, le numéro et la famille de protocoles associés au protocole TCP en utilisant la structure protoent.

---------------------------------------------------------------------------
gethostbyname()
=================

La fonction gethostbyname() en C est utilisée pour obtenir des informations sur un hôte à partir de son nom d'hôte ou de son adresse IP. Elle est souvent utilisée pour résoudre le nom d'un hôte en son adresse IP correspondante.

Voici la syntaxe de la fonction :

c

struct hostent *gethostbyname(const char *name);

    name : le nom de l'hôte ou l'adresse IP que l'on souhaite rechercher

La fonction renvoie un pointeur vers une structure hostent qui contient des informations sur l'hôte, telles que son nom, ses adresses IP et sa famille d'adresses.

Voici un exemple de code pour utiliser la fonction gethostbyname() pour obtenir les adresses IP d'un hôte à partir de son nom :

#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    const char *hostname = "www.google.com";
    struct hostent *host = gethostbyname(hostname);

    if (host == NULL)
    {
        perror("Erreur lors de la recherche de l'hôte");
        return 1;
    }

    printf("Nom de l'hôte : %s\n", host->h_name);

    for (int i = 0; host->h_addr_list[i] != NULL; i++)
    {
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
        printf("Adresse IP : %s\n", inet_ntoa(addr));
    }

    return 0;
}

Dans cet exemple, nous utilisons la fonction gethostbyname() pour obtenir les adresses IP de l'hôte www.google.com. Si la fonction renvoie NULL, nous affichons un message d'erreur en utilisant la fonction perror(). Sinon, nous affichons le nom de l'hôte et toutes les adresses IP associées à l'hôte en utilisant la structure hostent et la fonction inet_ntoa() pour convertir les adresses IP en chaînes de caractères.

---------------------------------------------------------------------------

getaddrinfo()
=================

La fonction getaddrinfo() en C est utilisée pour résoudre un nom d'hôte ou une adresse IP en une liste d'adresses de socket. Elle est très utile lorsqu'on souhaite établir une connexion réseau.

Voici la syntaxe de la fonction :

c

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints, struct addrinfo **res);

    node : le nom de l'hôte ou l'adresse IP que l'on souhaite rechercher
    service : le nom ou le numéro de port du service que l'on souhaite utiliser
    hints : un pointeur vers une structure addrinfo contenant des informations sur les critères de sélection de l'adresse
    res : un pointeur vers une liste chaînée de structures addrinfo contenant les adresses de socket trouvées

La fonction renvoie 0 si elle réussit et un code d'erreur si elle échoue.

Voici un exemple de code pour utiliser la fonction getaddrinfo() pour résoudre l'adresse IP d'un hôte :

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    const char *hostname = "www.google.com";
    const char *service = "http";

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result;
    int status = getaddrinfo(hostname, service, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "Erreur lors de la résolution de l'adresse : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (struct addrinfo *p = result; p != NULL; p = p->ai_next)
    {
        char ipstr[INET6_ADDRSTRLEN];
        void *addr;

        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("Adresse IP : %s\n", ipstr);
    }

    freeaddrinfo(result);
    return 0;
}

Dans cet exemple, nous utilisons la fonction getaddrinfo() pour résoudre l'adresse IP de l'hôte www.google.com sur le port http. Nous avons initialisé la structure addrinfo avec des critères de sélection pour l'adresse, tels que la famille d'adresses et le type de socket. Ensuite, nous avons parcouru la liste chaînée d'adresses de socket retournée par la fonction getaddrinfo() et affiché chaque adresse IP en utilisant la fonction inet_ntop() pour convertir l'adresse en chaîne de caractères. Enfin, nous avons libéré la mémoire allouée pour la liste chaînée d'adresses de socket avec la fonction freeaddrinfo().

---------------------------------------------------------------------------

freeaddrinfo()
=================

La fonction freeaddrinfo() en C est utilisée pour libérer la mémoire allouée par la fonction getaddrinfo() lorsqu'elle est utilisée pour résoudre une adresse de socket. Elle est utilisée pour éviter les fuites de mémoire dans les programmes qui utilisent getaddrinfo().

Voici la syntaxe de la fonction :

void freeaddrinfo(struct addrinfo *res);

    res : un pointeur vers la liste chaînée de structures addrinfo à libérer.

La fonction ne renvoie pas de valeur.

Voici un exemple de code pour utiliser la fonction freeaddrinfo() :

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main()
{
    const char *hostname = "www.google.com";
    const char *service = "http";

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result;
    int status = getaddrinfo(hostname, service, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "Erreur lors de la résolution de l'adresse : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Utilisation des adresses de socket...

    freeaddrinfo(result); // Libération de la mémoire allouée par getaddrinfo()

    return 0;
}

Dans cet exemple, nous utilisons la fonction getaddrinfo() pour résoudre l'adresse IP de l'hôte www.google.com sur le port http. Nous stockons les résultats dans une structure addrinfo. Après avoir utilisé les adresses de socket pour établir une connexion réseau ou effectuer d'autres opérations, nous utilisons la fonction freeaddrinfo() pour libérer la mémoire allouée par getaddrinfo(). Cette étape est importante pour éviter les fuites de mémoire dans le programme.

---------------------------------------------------------------------------

bind()
=================

La fonction bind() en C est utilisée pour lier un socket à une adresse IP et à un numéro de port spécifiques sur la machine locale. Cette fonction est souvent utilisée pour préparer un serveur à écouter des connexions entrantes.

Voici la syntaxe de la fonction :

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    sockfd : le descripteur de fichier du socket à lier.
    addr : un pointeur vers une structure sockaddr qui contient l'adresse IP et le numéro de port à lier.
    addrlen : la taille de la structure sockaddr.

La fonction renvoie un entier qui indique si l'opération a réussi ou non. Une valeur de retour de 0 indique que la liaison a réussi, tandis qu'une valeur de retour de -1 indique une erreur.

Voici un exemple de code pour utiliser la fonction bind() :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Erreur lors de la liaison du socket");
        exit(EXIT_FAILURE);
    }

    printf("Le socket est lié avec succès au port 8080\n");

    return 0;
}

Dans cet exemple, nous créons un socket avec la fonction socket(). Nous initialisons une structure sockaddr_in avec l'adresse IP locale INADDR_ANY et le numéro de port 8080. Nous utilisons ensuite la fonction bind() pour lier le socket à cette adresse et ce port. Si la liaison réussit, nous imprimons un message indiquant que le socket a été lié avec succès au port 8080.

---------------------------------------------------------------------------

connect()
=================

La fonction connect() en C est utilisée pour établir une connexion entre un client et un serveur distant en utilisant un socket. Cette fonction est souvent utilisée par les clients pour se connecter à un serveur distant.

Voici la syntaxe de la fonction :

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    sockfd : le descripteur de fichier du socket à utiliser pour la connexion.
    addr : un pointeur vers une structure sockaddr qui contient l'adresse IP et le numéro de port du serveur distant.
    addrlen : la taille de la structure sockaddr.

La fonction renvoie un entier qui indique si la connexion a réussi ou non. Une valeur de retour de 0 indique que la connexion a réussi, tandis qu'une valeur de retour de -1 indique une erreur.

Voici un exemple de code pour utiliser la fonction connect() :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("Erreur lors de la conversion de l'adresse IP");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Erreur lors de la connexion au serveur");
        exit(EXIT_FAILURE);
    }

    printf("Connexion au serveur réussie\n");

    return 0;
}

Dans cet exemple, nous créons un socket avec la fonction socket(). Nous initialisons une structure sockaddr_in avec l'adresse IP 127.0.0.1 et le numéro de port 8080. Nous utilisons ensuite la fonction inet_pton() pour convertir l'adresse IP en un format binaire utilisable par la fonction connect(). Enfin, nous utilisons la fonction connect() pour établir une connexion avec le serveur distant. Si la connexion réussit, nous imprimons un message indiquant que la connexion au serveur a réussi.

---------------------------------------------------------------------------

listen()
=================

La fonction listen() en C est utilisée pour marquer un socket comme un socket d'écoute, ce qui signifie qu'il peut être utilisé pour accepter les connexions entrantes d'autres sockets. Cette fonction est souvent utilisée par les serveurs pour attendre les connexions des clients.

Voici la syntaxe de la fonction :

int listen(int sockfd, int backlog);

    sockfd : le descripteur de fichier du socket à utiliser pour l'écoute.
    backlog : le nombre maximum de connexions en attente de traitement.

La fonction renvoie un entier qui indique si l'opération a réussi ou non. Une valeur de retour de 0 indique que l'opération a réussi, tandis qu'une valeur de retour de -1 indique une erreur.

Voici un exemple de code pour utiliser la fonction listen() :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Erreur lors de la liaison du socket");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Erreur lors de l'écoute sur le socket");
        exit(EXIT_FAILURE);
    }

    printf("Attente des connexions des clients...\n");

    return 0;
}

Dans cet exemple, nous créons un socket avec la fonction socket(). Nous initialisons une structure sockaddr_in avec l'adresse IP INADDR_ANY et le numéro de port 8080. Nous utilisons ensuite la fonction bind() pour lier le socket à l'adresse et au port spécifiés. Enfin, nous utilisons la fonction listen() pour marquer le socket comme un socket d'écoute avec une file d'attente maximale de 5 connexions. Si la fonction listen() réussit, nous imprimons un message indiquant que le serveur est en attente des connexions des clients.

---------------------------------------------------------------------------

accept()
=================

La fonction listen() en C est utilisée pour marquer un socket comme un socket d'écoute, ce qui signifie qu'il peut être utilisé pour accepter les connexions entrantes d'autres sockets. Cette fonction est souvent utilisée par les serveurs pour attendre les connexions des clients.

Voici la syntaxe de la fonction :

int listen(int sockfd, int backlog);

    sockfd : le descripteur de fichier du socket à utiliser pour l'écoute.
    backlog : le nombre maximum de connexions en attente de traitement.

La fonction renvoie un entier qui indique si l'opération a réussi ou non. Une valeur de retour de 0 indique que l'opération a réussi, tandis qu'une valeur de retour de -1 indique une erreur.

Voici un exemple de code pour utiliser la fonction listen() :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Erreur lors de la liaison du socket");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Erreur lors de l'écoute sur le socket");
        exit(EXIT_FAILURE);
    }

    printf("Attente des connexions des clients...\n");

    return 0;
}

Dans cet exemple, nous créons un socket avec la fonction socket(). Nous initialisons une structure sockaddr_in avec l'adresse IP INADDR_ANY et le numéro de port 8080. Nous utilisons ensuite la fonction bind() pour lier le socket à l'adresse et au port spécifiés. Enfin, nous utilisons la fonction listen() pour marquer le socket comme un socket d'écoute avec une file d'attente maximale de 5 connexions. Si la fonction listen() réussit, nous imprimons un message indiquant que le serveur est en attente des connexions des clients.

---------------------------------------------------------------------------

htons()
=================

La fonction htons() en C est utilisée pour convertir un entier court (deux octets) de l'ordre des octets de l'hôte à l'ordre des octets du réseau. Le terme "htons" signifie "Host TO Network Short".

Voici la syntaxe de la fonction :

unsigned short htons(unsigned short hostshort);

    hostshort : l'entier court de l'hôte à convertir.

La fonction renvoie l'entier court converti à l'ordre des octets du réseau.

Voici un exemple de code pour utiliser la fonction htons() :


#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned short hostshort = 1234;
    unsigned short netshort = htons(hostshort);

    printf("Entier court de l'hôte : %d\n", hostshort);
    printf("Entier court du réseau : %d\n", netshort);

    return 0;
}

Dans cet exemple, nous définissons une variable hostshort pour contenir un entier court de l'hôte de valeur 1234. Nous utilisons ensuite la fonction htons() pour convertir cet entier court à l'ordre des octets du réseau. Nous stockons le résultat dans une autre variable appelée netshort. Nous imprimons ensuite les deux valeurs pour voir la différence entre l'entier court de l'hôte et l'entier court du réseau.

---------------------------------------------------------------------------

htonl()
=================

La fonction htonl() en C est utilisée pour convertir un entier long (quatre octets) de l'ordre des octets de l'hôte à l'ordre des octets du réseau. Le terme "htonl" signifie "Host TO Network Long".

Voici la syntaxe de la fonction :

unsigned long int htonl(unsigned long int hostlong);

    hostlong : l'entier long de l'hôte à convertir.

La fonction renvoie l'entier long converti à l'ordre des octets du réseau.

Voici un exemple de code pour utiliser la fonction htonl() :

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned long int hostlong = 0x12345678;
    unsigned long int netlong = htonl(hostlong);

    printf("Entier long de l'hôte : 0x%x\n", hostlong);
    printf("Entier long du réseau : 0x%x\n", netlong);

    return 0;
}

Dans cet exemple, nous définissons une variable hostlong pour contenir un entier long de l'hôte de valeur 0x12345678. Nous utilisons ensuite la fonction htonl() pour convertir cet entier long à l'ordre des octets du réseau. Nous stockons le résultat dans une autre variable appelée netlong. Nous imprimons ensuite les deux valeurs en hexadécimal pour voir la différence entre l'entier long de l'hôte et l'entier long du réseau.

---------------------------------------------------------------------------

ntohs()
=================

La fonction ntohs() en C est utilisée pour convertir un entier court (deux octets) de l'ordre des octets du réseau à l'ordre des octets de l'hôte. Le terme "ntohs" signifie "Network TO Host Short".

Voici la syntaxe de la fonction :

unsigned short ntohs(unsigned short netshort);

    netshort : l'entier court du réseau à convertir.

La fonction renvoie l'entier court converti à l'ordre des octets de l'hôte.

Voici un exemple de code pour utiliser la fonction ntohs() :

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned short netshort = 0x3412;
    unsigned short hostshort = ntohs(netshort);

    printf("Entier court du réseau : 0x%x\n", netshort);
    printf("Entier court de l'hôte : 0x%x\n", hostshort);

    return 0;
}

Dans cet exemple, nous définissons une variable netshort pour contenir un entier court du réseau de valeur 0x3412. Nous utilisons ensuite la fonction ntohs() pour convertir cet entier court à l'ordre des octets de l'hôte. Nous stockons le résultat dans une autre variable appelée hostshort. Nous imprimons ensuite les deux valeurs en hexadécimal pour voir la différence entre l'entier court du réseau et l'entier court de l'hôte.

---------------------------------------------------------------------------

ntohl()
=================

La fonction ntohl() en C est utilisée pour convertir un entier long (quatre octets) de l'ordre des octets du réseau à l'ordre des octets de l'hôte. Le terme "ntohl" signifie "Network TO Host Long".

Voici la syntaxe de la fonction :

unsigned long ntohl(unsigned long netlong);

    netlong : l'entier long du réseau à convertir.

La fonction renvoie l'entier long converti à l'ordre des octets de l'hôte.

Voici un exemple de code pour utiliser la fonction ntohl() :

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned long netlong = 0x78563412;
    unsigned long hostlong = ntohl(netlong);

    printf("Entier long du réseau : 0x%lx\n", netlong);
    printf("Entier long de l'hôte : 0x%lx\n", hostlong);

    return 0;
}

Dans cet exemple, nous définissons une variable netlong pour contenir un entier long du réseau de valeur 0x78563412. Nous utilisons ensuite la fonction ntohl() pour convertir cet entier long à l'ordre des octets de l'hôte. Nous stockons le résultat dans une autre variable appelée hostlong. Nous imprimons ensuite les deux valeurs en hexadécimal pour voir la différence entre l'entier long du réseau et l'entier long de l'hôte.

---------------------------------------------------------------------------

inet_addr()
=================

La fonction inet_addr() en C est utilisée pour convertir une adresse IPv4 en format de chaîne de caractères (notation pointée) en un entier de 32 bits dans l'ordre des octets du réseau.

Voici la syntaxe de la fonction :

unsigned long inet_addr(const char *cp);

    cp : un pointeur vers une chaîne de caractères représentant l'adresse IPv4 en format de notation pointée.

La fonction renvoie l'adresse IPv4 en entier de 32 bits dans l'ordre des octets du réseau.

Voici un exemple de code pour utiliser la fonction inet_addr() :

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    char ip_str[] = "192.168.1.1";
    unsigned long ip = inet_addr(ip_str);

    printf("Adresse IP en entier : 0x%08lx\n", ip);

    return 0;
}

Dans cet exemple, nous définissons une variable ip_str contenant une adresse IPv4 en format de notation pointée. Nous utilisons ensuite la fonction inet_addr() pour convertir cette adresse en un entier de 32 bits dans l'ordre des octets du réseau. Nous stockons le résultat dans une variable appelée ip. Nous imprimons ensuite la valeur de ip en hexadécimal pour voir l'adresse IP en entier.

---------------------------------------------------------------------------

inet_ntoa()
=================

La fonction inet_ntoa() en C est utilisée pour convertir une adresse IPv4 en format binaire (entier de 32 bits dans l'ordre des octets du réseau) en une chaîne de caractères dans le format de notation pointée (par exemple, "192.168.1.1").

Voici la syntaxe de la fonction :

char *inet_ntoa(struct in_addr in);

    in : une structure in_addr contenant l'adresse IPv4 en format binaire.

La fonction renvoie une chaîne de caractères représentant l'adresse IPv4 dans le format de notation pointée.

Voici un exemple de code pour utiliser la fonction inet_ntoa() :

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned long ip = 0xC0A80101; // 192.168.1.1 en ordre des octets du réseau
    struct in_addr in;
    in.s_addr = ip;

    char *ip_str = inet_ntoa(in);

    printf("Adresse IP en notation pointée : %s\n", ip_str);

    return 0;
}

Dans cet exemple, nous définissons une variable ip contenant une adresse IPv4 en entier de 32 bits dans l'ordre des octets du réseau. Nous créons ensuite une structure in_addr appelée in et initialisons sa valeur avec l'adresse IP en format binaire. Nous utilisons ensuite la fonction inet_ntoa() pour convertir in en une chaîne de caractères représentant l'adresse IP dans le format de notation pointée. Nous stockons le résultat dans une variable appelée ip_str et imprimons la valeur de ip_str pour afficher l'adresse IP dans le format de notation pointée.

---------------------------------------------------------------------------

send()
=================

La fonction send() en C est utilisée pour envoyer des données via une socket.

Voici la syntaxe de la fonction :

ssize_t send(int sockfd, const void *buf, size_t len, int flags);

    sockfd : le descripteur de fichier de la socket à utiliser pour l'envoi des données.
    buf : un pointeur vers le tampon contenant les données à envoyer.
    len : la taille des données à envoyer en octets.
    flags : des options pour l'envoi.

La fonction renvoie le nombre d'octets envoyés ou -1 si une erreur s'est produite.

Voici un exemple de code pour utiliser la fonction send() :

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char *hello = "Hello, world!";
    ssize_t num_sent;

    // Créer la socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Initialiser la structure d'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("Adresse invalide / non supportée");
        exit(EXIT_FAILURE);
    }

    // Connecter à un serveur distant
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Erreur lors de la connexion");
        exit(EXIT_FAILURE);
    }

    // Envoyer les données
    num_sent = send(sockfd, hello, strlen(hello), 0);
    if (num_sent < 0)
    {
        perror("Erreur lors de l'envoi des données");
        exit(EXIT_FAILURE);
    }
    printf("Nombre d'octets envoyés : %zd\n", num_sent);

    // Fermer la socket
    close(sockfd);

    return 0;
}

Dans cet exemple, nous créons une socket, initialisons une structure d'adresse pour le serveur, nous connectons à un serveur distant, envoyons une chaîne de caractères, et enfin fermons la socket.

Notez que dans cet exemple, nous envoyons une chaîne de caractères en utilisant la fonction send(). La fonction strlen() est utilisée pour déterminer la longueur de la chaîne de caractères à envoyer. Le nombre d'octets envoyés est stocké dans la variable num_sent, qui est ensuite imprimée à l'écran.

---------------------------------------------------------------------------

recv()
=================

La fonction recv() en C est utilisée pour recevoir des données d'une socket. Elle prend les paramètres suivants :

int recv(int sockfd, void *buf, size_t len, int flags);

    sockfd: le descripteur de fichier de la socket à partir de laquelle les données sont reçues.
    buf: un pointeur vers le tampon dans lequel les données reçues sont stockées.
    len: la longueur maximale des données à recevoir.
    flags: les indicateurs spéciaux qui modifient le comportement de la fonction recv().

La fonction recv() renvoie le nombre de bytes reçus, qui peut être plus petit que la longueur spécifiée len si les données sont incomplètes ou s'il y a une erreur.

Voici un exemple de code qui illustre comment utiliser la fonction recv() pour recevoir des données à partir d'une socket :

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Erreur lors de la création de la socket.\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Erreur lors de la connexion au serveur.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};
    int valread = recv(sockfd, buffer, 1024, 0);
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}

Dans cet exemple, la fonction recv() est utilisée pour recevoir des données à partir d'une socket connectée. Le serveur envoie une chaîne de caractères au client, qui utilise la fonction recv() pour la recevoir. La chaîne de caractères est stockée dans un tampon buffer et affichée sur la console à l'aide de printf().

---------------------------------------------------------------------------

lseek()
=================

La fonction lseek() en C est utilisée pour déplacer le pointeur de fichier (file pointer) d'un fichier ouvert vers une position spécifiée. Le pointeur de fichier est utilisé pour suivre la position actuelle dans un fichier et peut être déplacé en avant ou en arrière pour permettre l'écriture ou la lecture à partir d'une position particulière.

La fonction lseek() prend en entrée le descripteur de fichier (file descriptor), la position vers laquelle le pointeur de fichier doit être déplacé et le mode de déplacement (début du fichier, position courante ou fin du fichier). La fonction retourne la nouvelle position du pointeur de fichier ou -1 en cas d'erreur.

Voici un exemple de code pour déplacer le pointeur de fichier à partir de la position actuelle vers 10 octets plus loin :

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(fd, 10, SEEK_CUR);
    if (offset == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    printf("New offset: %ld\n", (long) offset);

    close(fd);
    return 0;
}

Dans cet exemple, nous ouvrons le fichier "test.txt" en mode lecture seule en utilisant la fonction open(). Ensuite, nous utilisons la fonction lseek() pour déplacer le pointeur de fichier de 10 octets à partir de la position actuelle. La valeur retournée par lseek() est stockée dans la variable offset, qui est ensuite affichée à l'écran. Enfin, nous fermons le fichier en utilisant la fonction close().

---------------------------------------------------------------------------

fstat()
=================

La fonction fstat() en C est utilisée pour obtenir des informations sur un fichier ouvert à l'aide de son descripteur de fichier (file descriptor). Les informations renvoyées incluent la taille du fichier, les permissions, la date de modification, etc.

La fonction fstat() prend en entrée un descripteur de fichier et un pointeur vers une structure struct stat, qui sera remplie avec les informations sur le fichier. La fonction retourne 0 en cas de succès et -1 en cas d'erreur.

Voici un exemple de code pour utiliser la fonction fstat() pour obtenir la taille d'un fichier :

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1)
    {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    printf("Size of file: %ld bytes\n", (long) file_stat.st_size);

    close(fd);
    return 0;
}

Dans cet exemple, nous ouvrons le fichier "test.txt" en mode lecture seule en utilisant la fonction open(). Ensuite, nous utilisons la fonction fstat() pour obtenir les informations sur le fichier, en passant le descripteur de fichier fd et un pointeur vers une structure struct stat appelée file_stat. Nous pouvons ensuite accéder à la taille du fichier à l'aide de l'attribut st_size de la structure file_stat. Enfin, nous fermons le fichier en utilisant la fonction close().

---------------------------------------------------------------------------

fcntl()
=================

La fonction fcntl() en C est utilisée pour effectuer diverses opérations de contrôle sur des fichiers ouverts. Elle peut être utilisée pour lire ou modifier les propriétés d'un descripteur de fichier, telles que le mode d'accès, le verrouillage de fichier, etc.

La fonction fcntl() prend trois arguments : le descripteur de fichier sur lequel l'opération doit être effectuée, l'opération à effectuer et un troisième argument qui dépend de l'opération.

Voici quelques exemples d'utilisation de la fonction fcntl():

    Modifier le mode d'accès d'un fichier :

#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Obtient les flags actuels
    int flags = fcntl(fd, F_GETFL);

    // Définit le flag O_APPEND pour permettre l'écriture à la fin du fichier
    fcntl(fd, F_SETFL, flags | O_APPEND);

    close(fd);

    return 0;
}

Récupérer les flags d'un descripteur de fichier :

#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Obtient les flags actuels
    int flags = fcntl(fd, F_GETFL);

    // Vérifie si le flag O_RDWR est défini
    if (flags & O_RDWR)
    {
        printf("Le descripteur de fichier permet la lecture et l'écriture\n");
    }

    close(fd);

    return 0;
}

Verrouiller un fichier :

#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Initialise une structure flock pour définir le verrouillage
    struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};

    // Tente d'obtenir le verrou exclusif sur le fichier
    if (fcntl(fd, F_SETLK, &fl) == -1)
    {
        perror("fcntl");
        return 1;
    }

    printf("Le fichier est maintenant verrouillé\n");

    // Attend 10 secondes avant de relâcher le verrou
    sleep(10);

    // Définit la structure flock pour libérer le verrou
    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1)
    {
        perror("fcntl");
        return 1;
    }

    printf("Le fichier est maintenant déverrouillé\n");

    close(fd);

    return 0;
}


---------------------------------------------------------------------------

poll()
=================

La fonction poll() est une fonction système de bas niveau en C qui permet de surveiller plusieurs descripteurs de fichiers simultanément pour les opérations d'entrée/sortie. Elle permet d'attendre qu'une ou plusieurs opérations d'E/S soient disponibles sur plusieurs descripteurs de fichiers ou sur un seul.

La fonction prend en entrée un tableau de structures struct pollfd qui contient des informations sur les descripteurs de fichiers à surveiller, le nombre de descripteurs de fichiers à surveiller et un temps d'attente maximum en millisecondes. La fonction retourne le nombre de descripteurs de fichiers qui sont prêts pour les opérations d'entrée/sortie ou 0 si le délai d'attente a expiré.

Voici un exemple d'utilisation de la fonction poll() pour surveiller deux descripteurs de fichiers (fd1 et fd2) pour les opérations de lecture :

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

int main()
{
    struct pollfd fds[2];
    int timeout = 5000; // 5 secondes de délai d'attente
    int ret;

    // Ouverture des deux descripteurs de fichiers à surveiller
    int fd1 = open("fichier1.txt", O_RDONLY);
    int fd2 = open("fichier2.txt", O_RDONLY);

    // Initialisation des structures pollfd
    fds[0].fd = fd1;
    fds[0].events = POLLIN; // attendre les données en entrée
    fds[1].fd = fd2;
    fds[1].events = POLLIN;

    // Attente des événements sur les deux descripteurs de fichiers
    ret = poll(fds, 2, timeout);

    if (ret == -1)
    {
        perror("poll");
        exit(EXIT_FAILURE);
    }
    else if (ret == 0)
    {
        printf("Timeout expiré\n");
    }
    else
    {
        // Un ou plusieurs descripteurs de fichiers sont prêts pour l'E/S
        if (fds[0].revents & POLLIN)
        {
            printf("Données disponibles sur fd1\n");
            // lire les données sur fd1
        }
        if (fds[1].revents & POLLIN)
        {
            printf("Données disponibles sur fd2\n");
            // lire les données sur fd2
        }
    }

    // Fermeture des descripteurs de fichiers
    close(fd1);
    close(fd2);

    return 0;
}

Dans cet exemple, poll() est utilisé pour surveiller deux descripteurs de fichiers (fd1 et fd2) pour les opérations d'entrée/sortie en attente. Les deux descripteurs de fichiers sont initialisés avec POLLIN pour attendre les données en entrée. La fonction poll() est appelée avec un délai d'attente de 5 secondes maximum. Si les données sont disponibles sur l'un des descripteurs de fichiers surveillés, les informations de retour de poll() indiquent quel descripteur de fichier est prêt pour l'E/S et les données peuvent être lues à partir de ce descripteur de fichier.

---------------------------------------------------------------------------

