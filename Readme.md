fy_irc

------------------------------------------------------------------------------------

#include <sys/socket.h> 

<!-- int socket(int domaine , int type , int protocole ); -->

socket () crée un point de terminaison pour la communication et renvoie un 
descripteur de fichier qui fait référence à ce point de terminaison. Le descripteur de fichier 
renvoyé par un appel réussi sera le 
descripteur de fichier portant le numéro le plus bas qui n'est pas actuellement ouvert pour le processus. 

L' argument domaine spécifie un domaine de communication ; ceci 
sélectionne la famille de protocole qui sera utilisée pour la communication. 
Ces familles sont définies dans <sys/socket.h> . Les formats 
actuellement compris par le noyau Linux incluent : 

Nom Objectif Page de manuel AF_UNIX       Communication locale                        
unix(7) 
AF_LOCAL      Synonyme de AF_UNIX 
AF_INET       IPv4 Protocoles Internet                     ip(7) 
AF_AX25       Radio amateur Protocole AX.25                ax25 (4)
AF_IPX        IPX - Protocoles Novell
AF_APPLETALK AppleTalk                                   ddp(7) 
AF_X25        Protocole ITU-T X.25 / ISO-8208              x25(7) 
AF_INET6      Protocoles Internet IPv6                     ipv6(7) 
AF_DECnet     Sockets de protocole DECet
AF_KEY        Protocole de gestion des clés, à l'origine
            développé pour une utilisation avec IPsec AF_NETLINK    Périphérique d'interface utilisateur du noyau                netlink(7) AF_PACKET     Paquet d'interface de paquets de bas niveau                  (7) AF_RDS        Protocole RDS (Reliable Datagram Sockets)    rds (7)
                                                        rds-rdma (7)
AF_PPPOX      Couche de transport PPP générique, pour la configuration 
            tunnels L2 (L2TP et PPPoE) AF_LLC        
            Protocole de contrôle de liaison logique (IEEE 802.2 LLC) AF_IB         Adressage natif InfiniBand
AF_MPLS  

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h> 

<!-- int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
     int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen); -->

getsockopt () et setsockopt () manipulent les options pour la socket référencée par le descripteur de fichier sockfd . Des options peuvent exister à plusieurs niveaux de protocole ; ils sont toujours présents au niveau de socket le plus élevé.
Lors de la manipulation des options de socket, le niveau auquel l'option réside et le nom de l'option doivent être spécifiés. Pour manipuler les options au niveau de l'API des sockets, level est spécifié comme SOL_SOCKET . Pour manipuler des options à tout autre niveau, le numéro de protocole du protocole approprié contrôlant l'option est fourni. Par exemple, pour indiquer qu'une option doit être interprétée par le protocole TCP , level doit être défini sur le numéro de protocole de TCP ; voir getprotoent (3) .

Les arguments optval et optlen sont utilisés pour accéder aux valeurs d'option pour setsockopt (). Pour getsockopt (), ils identifient un tampon dans lequel la valeur de la ou des options demandées doit être renvoyée. Pour getsockopt (), optlen est un argument valeur-résultat, contenant initialement la taille du tampon pointé par optval , et modifié au retour pour indiquer la taille réelle de la valeur renvoyée. Si aucune valeur d'option ne doit être fournie ou renvoyée, optval peut être NULL.

Optname et toutes les options spécifiées sont transmises sans être interprétées au module de protocole approprié pour interprétation. Le fichier inclus < sys/socket.h > contient les définitions des options au niveau du socket, décrites ci-dessous. Les options à d'autres niveaux de protocole varient en format et en nom ; consultez les entrées appropriées dans la section 4 du manuel.

La plupart des options au niveau du socket utilisent un argument int pour optval . Pour setsockopt (), l'argument doit être différent de zéro pour activer une option booléenne, ou zéro si l'option doit être désactivée.

Pour une description des options de socket disponibles, voir socket (7) et les pages de manuel du protocole approprié.


Valeur de retour
En cas de succès, zéro est renvoyé. En cas d'erreur, -1 est renvoyé et errno est défini de manière appropriée.

------------------------------------------------------------------------------------

#include <sys/socket.h>

<!-- int getsockname(int sockfd , struct sockaddr *restrict addr , socklen_t *restrict addrlen ); -->

getsockname () renvoie l'adresse actuelle à laquelle la socket
sockfd est liée, dans le tampon pointé par addr . L' adrlen
l'argument doit être initialisé pour indiquer la quantité d'espace
(en octets) pointé par addr . Au retour, il contient la valeur réelle
taille de l'adresse de socket.

L'adresse renvoyée est tronquée si le tampon fourni est trop
petit; dans ce cas, addrlen renverra une valeur supérieure à ce qui était
fourni à l'appel.


VALEUR DE RETOUR        
En cas de succès, zéro est renvoyé. En cas d'erreur, -1 est renvoyé et
errno est défini pour indiquer l'erreur.

------------------------------------------------------------------------------------

#include <netdb.h>

<!-- struct protoent *getprotoent(void);

struct protoent *getprotobyname(const char * name );

struct protoent *getprotobynumber(int  proto );

void setprotoent(int  stayopen );

void endprotoent(void); -->

Description
La fonction getprotoent () lit l'entrée suivante dans la base de données des protocoles (voir protocoles (5)) et renvoie une structure protoent contenant les champs séparés de l'entrée. Une connexion est ouverte à la base de données si nécessaire.

La fonction getprotobyname () renvoie une structure de protocole pour l'entrée de la base de données qui correspond au nom de protocole name . Une connexion est ouverte à la base de données si nécessaire.

La fonction getprotobynumber () renvoie une structure de protocole pour l'entrée de la base de données qui correspond au numéro de protocole number . Une connexion est ouverte à la base de données si nécessaire.

La fonction setprotoent () ouvre une connexion à la base de données et définit l'entrée suivante sur la première entrée. Si stayopen est différent de zéro, la connexion à la base de données ne sera pas fermée entre les appels à l'une des fonctions getproto* ().

La fonction endprotoent () ferme la connexion à la base de données.

La structure du protoent est définie dans < netdb.h > comme suit :

struct protoent {
    caractère *p_name ; /* nom officiel du protocole */
    char **p_aliases ; /* liste d'alias */
    int p_proto; /* numéro de protocole */
}
Les membres de la structure du protoent sont :
nom_p
Le nom officiel du protocole.

p_aliases
Une liste terminée par NULL de noms alternatifs pour le protocole.
p_proto
Le numéro de protocole.


Valeur de retour
Les fonctions getprotoent (), getprotobyname () et getprotobynumber () renvoient un pointeur vers une structure de protocole allouée statiquement , ou un pointeur NULL si une erreur se produit ou si la fin du fichier est atteinte.

------------------------------------------------------------------------------------

#include <netdb.h >
extern int h_errno;

<!-- struct hostent *gethostbyname(const char * name ); -->

#include <sys/socket.h >        /* pour AF_INET */

<!-- struct hostent *gethostbyaddr(const void * addr , socklen_t  len ​​​​, type int  );

void sethostent(int  stayopen );

void endhostent(void);

void herror(const char * s );

const char *hstrerror(int  err );

/* Extension système V/POSIX */
 struct hostent *gethostent(void);

/* Extensions GNU */
 struct hostent *gethostbyname2(const char * name , int  af );

int gethostent_r(
        struct hostent * ret , char * buf , size_t  buflen ,
        struct hostent ** résultat , int * h_errnop );

int gethostbyaddr_r(const void * addr , socklen_t  len ​​, int  type ,
        struct hostent * ret , char * buf , size_t  buflen ,
        struct hostent ** résultat , int * h_errnop );

int gethostbyname_r(const char * nom ,
        struct hostent * ret , char * buf , size_t  buflen ,
        struct hostent ** résultat , int * h_errnop );

int gethostbyname2_r(const char * nom , int  af,
         struct hostent * ret , char * buf , size_t  buflen ,
        struct hostent ** résultat , int * h_errnop ); -->

Configuration requise pour les macros de test de fonctionnalité pour la glibc (voir feature_test_macros (7)) :
gethostbyname2 (), gethostent_r (), gethostbyaddr_r (), gethostbyname_r (), gethostbyname2_r ():
_BSD_SOURCE || _SVID_SOURCE
herror (), hstrerror () :
Depuis glibc 2.8 :
_BSD_SOURCE || _SVID_SOURCE || _GNU_SOURCE
Avant glibc 2.8 :
aucun
Description
Les fonctions gethostbyname* () et gethostbyaddr* () sont obsolètes. Les applications doivent utiliser getaddrinfo (3) et getnameinfo (3) à la place.

La fonction gethostbyname () renvoie une structure de type hostent pour le nom d'hôte donné . Ici, name est soit un nom d'hôte, soit une adresse IPv4 en notation standard par points (comme pour inet_addr (3)), soit une adresse IPv6 en notation deux points (et éventuellement pointée). (Voir RFC 1884 pour la description des adresses IPv6.) Si name est une adresse IPv4 ou IPv6, aucune recherche n'est effectuée et gethostbyname () copie simplement name dans le champ h_name et son équivalent struct in_addr dans le champ h_addr_list[0] du structure hostent retournée . Siname ne se termine pas par un point et que la variable d'environnement HOSTALIASES est définie, le fichier d'alias pointé par HOSTALIASES sera d'abord recherché pour name (voir hostname (7) pour le format de fichier). Le domaine actuel et ses parents sont recherchés à moins que le nom ne se termine par un point.

La fonction gethostbyaddr () renvoie une structure de type hostent pour l'adresse d'hôte donnée addr de longueur len et de type d'adresse type . Les types d'adresse valides sont AF_INET et AF_INET6 . L'argument de l'adresse de l'hôte est un pointeur vers une structure d'un type dépendant du type d'adresse, par exemple une structure in_addr * (probablement obtenue via un appel à inet_addr (3)) pour le type d'adresse AF_INET .

La fonction sethostent () spécifie, si stayopen est vrai (1), qu'une socket TCP connectée doit être utilisée pour les requêtes du serveur de noms et que la connexion doit rester ouverte lors des requêtes successives. Sinon, les requêtes de serveur de noms utiliseront des datagrammes UDP.

La fonction endhostent () met fin à l'utilisation d'une connexion TCP pour les requêtes de serveur de noms.

La fonction (obsolète) herror () imprime le message d'erreur associé à la valeur actuelle de h_errno sur stderr .

La fonction (obsolète) hstrerror () prend un numéro d'erreur (généralement h_errno ) et renvoie la chaîne de message correspondante.

Les requêtes de nom de domaine effectuées par gethostbyname () et gethostbyaddr () utilisent une combinaison de tout ou partie du serveur de noms nommé (8), une ligne discontinue de /etc/hosts et le service d'information réseau (NIS ou YP) , selon le contenu de la ligne de commande dans /etc/host.conf . L'action par défaut consiste à interroger nommé (8), suivi de /etc/hosts .

La structure hostent est définie dans < netdb.h > comme suit :

structure hostent {
    char *h_name ; /* nom officiel de l'hôte */
    char **h_aliases ; /* liste d'alias */
    int h_addrtype ; /* type d'adresse hôte */
    entier h_longueur ; /* longueur de l'adresse */
    caractère **h_addr_list ; /* liste des adresses */
}
#define h_addr h_addr_list[0] /* pour la rétrocompatibilité */
Les membres de la structure d'accueil sont :
h_name
Le nom officiel de l'hôte.

h_alias
Un tableau de noms alternatifs pour l'hôte, terminé par un pointeur NULL.
h_addrtype
Le type d'adresse ; toujours AF_INET ou AF_INET6 actuellement.
longueur_h
La longueur de l'adresse en octets.
h_addr_list
Un tableau de pointeurs vers les adresses réseau de l'hôte (dans l'ordre des octets du réseau), terminé par un pointeur NULL.
h_addr
La première adresse dans h_addr_list pour le retour

compatibilité.


Valeur de retour
Les fonctions gethostbyname () et gethostbyaddr () renvoient la structure hostent ou un pointeur NULL si une erreur se produit. En cas d'erreur, la variable h_errno contient un numéro d'erreur. Lorsqu'elle n'est pas NULL, la valeur de retour peut pointer vers des données statiques, voir les notes ci-dessous.

les erreurs
La variable h_errno peut prendre les valeurs suivantes :

HÉBERGEUR NON TROUVÉ
L'hôte spécifié est inconnu.
NO_ADDRESS ou NO_DATA
Le nom demandé est valide mais n'a pas d'adresse IP.
NO_RECOVERY
Une erreur de serveur de noms irrécupérable s'est produite.
ESSAYER À NOUVEAU
Une erreur temporaire s'est produite sur un serveur de noms faisant autorité. Réessayez plus tard.
Des dossiers
/etc/host.conf

fichier de configuration du résolveur
/etc/hosts
fichier de base de données hôte
/etc/nsswitch.conf
configuration du commutateur de service de noms

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

<!-- int getaddrinfo(const char * node , const char * service ,
                const struct addrinfo * conseils ,
                struct addrinfo ** res );

void freeaddrinfo(struct addrinfo * res ); -->

const char *gai_strerror(int  code d'erreur );
Configuration requise pour les macros de test de fonctionnalité pour la glibc (voir feature_test_macros (7)) :
getaddrinfo (), freeaddrinfo (), gai_strerror () :
_POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE
Description
Étant donné node et service , qui identifient un hôte Internet et un service, getaddrinfo () renvoie une ou plusieurs structures addrinfo , chacune contenant une adresse Internet qui peut être spécifiée dans un appel à bind (2) ou connect (2). La fonction getaddrinfo () combine les fonctionnalités fournies par les fonctions gethostbyname (3) et getservbyname (3) dans une seule interface, mais contrairement à ces dernières fonctions, getaddrinfo () est réentrante et permet aux programmes d'éliminer les dépendances IPv4 contre IPv6.

La structure addrinfo utilisée par getaddrinfo () contient les champs suivants :

<!-- structure addrinfo {
    int ai_flags ;
    int ai_family ;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen ;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
} ; -->

L' argument hints pointe vers une structure addrinfo qui spécifie les critères de sélection des structures d'adresse de socket renvoyées dans la liste pointée par res . Si hints n'est pas NULL, il pointe vers une structure addrinfo dont ai_family , ai_socktype et ai_protocol spécifient des critères qui limitent l'ensemble d'adresses de socket renvoyées par getaddrinfo (), comme suit :
ai_family

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

<!-- int getaddrinfo(const char * node , const char * service ,
                const struct addrinfo * conseils ,
                struct addrinfo ** res );

void freeaddrinfo(struct addrinfo * res );

const char *gai_strerror(int  code d'erreur ); -->

Configuration requise pour les macros de test de fonctionnalité pour la glibc (voir feature_test_macros (7)) :
getaddrinfo (), freeaddrinfo (), gai_strerror () :
_POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE

Description
Étant donné node et service , qui identifient un hôte Internet et un service, getaddrinfo () renvoie une ou plusieurs structures addrinfo , chacune contenant une adresse Internet qui peut être spécifiée dans un appel à bind (2) ou connect (2). La fonction getaddrinfo () combine les fonctionnalités fournies par les fonctions gethostbyname (3) et getservbyname (3) dans une seule interface, mais contrairement à ces dernières fonctions, getaddrinfo () est réentrante et permet aux programmes d'éliminer les dépendances IPv4 contre IPv6.

------------------------------------------------------------------------------------

std::bind

simple(1)	
<!-- template <class Fn, class... Args>  /* unspecified */ bind (Fn&& fn, Args&&... args); -->
with return type (2)	
<!-- template <class Ret, class Fn, class... Args>  /* unspecified */ bind (Fn&& fn, Args&&... args); -->

Renvoie un objet fonction basé sur fn , mais avec ses arguments liés à args .

Chaque argument peut soit être lié à une valeur , soit être un espace réservé :
- S'il est lié à une valeur , l'appel de l'objet fonction renvoyé utilisera toujours cette valeur comme argument.
- Si un espace réservé , l'appel de l'objet fonction renvoyé transmet un argument passé à l'appel (celui dont le numéro d'ordre est spécifié par l'espace réservé).

L'appel de l'objet renvoyé renvoie le même type que fn , sauf si un type de retour spécifique est spécifié commeRet (2) (notez queRetest le seul paramètre de modèle qui ne peut pas être implicitement déduit par les arguments passés à cette fonction).

Le type de l'objet renvoyé a les propriétés suivantes :
Son appel fonctionnel renvoie la même chose que fn avec ses arguments liés à args... (ou transmis, pour les espaces réservés ).
Pour (1) , il peut avoir un membretype_résultat: siFNest un pointeur vers une fonction ou un type de fonction membre, il est défini comme un alias de son type de retour. Sinon, il est défini commeFn :: type_résultat, si un tel type de membre existe.
Pour (2) , il a un membretype_résultat, défini comme un alias deRet.
Il est constructible par déplacement et, si le type de tous ses arguments est constructible par copie , il est également constructible par copie . Les deux constructeurs ne lancent jamais, à condition qu'aucun des constructeurs correspondants des types de désintégration deFNetArf...lancer.

------------------------------------------------------------------------------------

#include <sys/socket.h>

<!-- int connect(int socket , const struct sockaddr * address , socklen_t address_len ); -->

Description
La fonction connect () doit tenter d'établir une connexion sur une socket. La fonction prend les arguments suivants :

socket
Spécifie le descripteur de fichier associé au socket.
adresse
Pointe vers une structure sockaddr contenant l'adresse du pair. La longueur et le format de l'adresse dépendent de la famille d'adresses du socket.
adresse_len
Spécifie la longueur de la structure sockaddr pointée par l' argument d'adresse .

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h>

<!-- int listen(int sockfd, int backlog); -->

Description
listen () marque la socket référencée par sockfd comme une socket passive, c'est-à-dire comme une socket qui sera utilisée pour accepter les demandes de connexion entrantes à l'aide de accept (2) .
L' argument sockfd est un descripteur de fichier qui fait référence à un socket de type SOCK_STREAM ou SOCK_SEQPACKET .

L' argument backlog définit la longueur maximale à laquelle la file d'attente des connexions en attente pour sockfd peut croître. Si une demande de connexion arrive lorsque la file d'attente est pleine, le client peut recevoir une erreur avec une indication ECONNREFUSED ou, si le protocole sous-jacent prend en charge la retransmission, la demande peut être ignorée de sorte qu'une nouvelle tentative de connexion ultérieure réussisse.

Valeur de retour
En cas de succès, zéro est renvoyé. En cas d'erreur, -1 est renvoyé et errno est défini de manière appropriée.


------------------------------------------------------------------------------------

#include <sys/socket.h>

<!-- int accept(int socket , struct sockaddr *restrict address ,
socklen_t *restrict address_len ); -->

Description
La fonction accept () doit extraire la première connexion de la file d'attente des connexions en attente, créer une nouvelle socket avec le même protocole de type de socket et la même famille d'adresses que la socket spécifiée, et allouer un nouveau descripteur de fichier pour cette socket.

La fonction accept () prend les arguments suivants :

prise
Spécifie un socket qui a été créé avec socket (), a été lié à une adresse avec bind () et a émis un appel réussi à listen ().
adresse
Soit un pointeur nul, soit un pointeur vers une structure sockaddr où l'adresse de la prise de connexion doit être renvoyée.
adresse_len
Pointe vers une structure socklen_t qui, en entrée, spécifie la longueur de la structure sockaddr fournie et, en sortie, la longueur de l'adresse stockée.
Si address n'est pas un pointeur nul, l'adresse du pair pour la connexion acceptée doit être stockée dans la structure sockaddr pointée par address , et la longueur de cette adresse doit être stockée dans l'objet pointé par address_len .

Si la longueur réelle de l'adresse est supérieure à la longueur de la structure sockaddr fournie , l'adresse stockée doit être tronquée.

Si le protocole autorise les connexions par des clients non liés et que l'homologue n'est pas lié, la valeur stockée dans l'objet pointé par l' adresse n'est pas spécifiée.

Si la file d'attente d'écoute est vide de demandes de connexion et que O_NONBLOCK n'est pas défini sur le descripteur de fichier pour la socket, accept () doit bloquer jusqu'à ce qu'une connexion soit présente. Si la file d'attente listen () est vide de demandes de connexion et que O_NONBLOCK est défini sur le descripteur de fichier pour la socket, accept () doit échouer et définir errno sur [EAGAIN] ou [EWOULDBLOCK].

Le socket accepté ne peut pas lui-même accepter plus de connexions. La prise d'origine reste ouverte et peut accepter plus de connexions.


Valeur de retour
En cas de réussite, accept () doit renvoyer le descripteur de fichier non négatif de la socket acceptée. Sinon, -1 doit être renvoyé et errno doit être défini pour indiquer l'erreur.

------------------------------------------------------------------------------------

#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

Description
<!-- La fonction htonl () convertit l'entier non signé hostlong de l'ordre des octets de l'hôte vers l'ordre des octets du réseau.
La fonction htons () convertit l'entier court non signé hostshort de l'ordre des octets de l'hôte à l'ordre des octets du réseau.

La fonction ntohl () convertit l'entier non signé netlong de l'ordre des octets du réseau à l'ordre des octets de l'hôte.

La fonction ntohs () convertit l'entier court non signé netshort de l'ordre des octets du réseau à l'ordre des octets de l'hôte. -->

Sur le i386, l'ordre des octets de l'hôte est l'octet le moins significatif en premier, tandis que l'ordre des octets du réseau, tel qu'il est utilisé sur Internet, est l'octet le plus significatif en premier.

Se conformer à
POSIX.1-2001.
Certains systèmes nécessitent l'inclusion de < netinet/in.h > au lieu de < arpa/inet.h > .

------------------------------------------------------------------------------------

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

<!-- int inet_aton(const char * cp , struct in_addr * inp );

in_addr_t inet_addr(const char * cp );

in_addr_t inet_network(const char * cp );

char *inet_ntoa(struct in_addr  in );

struct in_addr inet_makeaddr(int  net , int  host );

in_addr_t inet_lnaof(struct in_addr  in );

in_addr_t inet_netof(struct in_addr  in ); -->

Configuration requise pour les macros de test de fonctionnalité pour la glibc (voir feature_test_macros (7)) :
net_attack (), net_attack () : _BSD_SOURCE || _SVID_SOURCE
Description
inet_aton () convertit l'adresse de l'hôte Internet cp de la notation IPv4 chiffres-points en une forme binaire (dans l'ordre des octets du réseau) et la stocke dans la structure vers laquelle inp pointe. inet_aton () renvoie non nul si l'adresse est valide, zéro sinon.

La structure in_addr utilisée dans inet_ntoa (), inet_makeaddr (), inet_lnaof () et inet_netof () est définie dans < netinet/in.h > comme :

<!-- typedef uint32_t in_addr_t ;

structure in_addr {
    in_addr_t s_addr ;
} ; -->

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h>

<!-- ssize_t send(int  sockfd , const void * buf , size_t  len ​​, int  flags );

ssize_t sendto(int  sockfd , const void * buf , size_t  len ​​, int  flags ,
               const struct sockaddr * dest_addr , socklen_t  addrlen );

ssize_t sendmsg(int  sockfd , const struct msghdr * msg , int  flags ); -->

Description
Les appels système send (), sendto () et sendmsg () sont utilisés pour transmettre un message à une autre socket.

L' appel send () ne peut être utilisé que lorsque la socket est dans un état connecté (de sorte que le destinataire prévu est connu). La seule différence entre send () et write (2) est la présence de flags . Avec un argument à zéro drapeau , send () est équivalent à write (2).

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/socket.h>

<!-- ssize_t recv(int  sockfd , void * buf , size_t  len ​​, int  flags );

ssize_t recvfrom(int  sockfd , void * buf , size_t  len ​​, int  flags ,
                 struct sockaddr * src_addr , socklen_t * addrlen );

ssize_t recvmsg(int  sockfd , struct msghdr * msg , int  flags ); -->

Description
Les appels recvfrom () et recvmsg () sont utilisés pour recevoir des messages d'un socket, et peuvent être utilisés pour recevoir des données sur un socket, qu'il soit ou non orienté connexion.

Si src_addr n'est pas NULL et que le protocole sous-jacent fournit l'adresse source, cette adresse source est renseignée. Lorsque src_addr est NULL, rien n'est renseigné ; dans ce cas, addrlen n'est pas utilisé et doit également être NULL. L'argument addrlen est un argument valeur-résultat, que l'appelant doit initialiser avant l'appel à la taille du tampon associé à src_addr , et modifié au retour pour indiquer la taille réelle de l'adresse source. L'adresse renvoyée est tronquée si le tampon fourni est trop petit ; dans ce cas, addrlen renverra une valeur supérieure à celle fournie à l'appel.

L' appel recv () n'est normalement utilisé que sur une socket connectée (voir connect (2)) et est identique à recvfrom () avec un argument NULL src_addr .

Les trois routines renvoient la longueur du message en cas de réussite. Si un message est trop long pour tenir dans la mémoire tampon fournie, les octets en excès peuvent être ignorés en fonction du type de socket à partir duquel le message est reçu.

Si aucun message n'est disponible sur la socket, les appels de réception attendent l'arrivée d'un message, à moins que la socket ne soit non bloquante (voir fcntl (2)), auquel cas la valeur -1 est renvoyée et la variable externe errno est définie sur EAGAIN ou EWOULDBLOCK . Les appels de réception renvoient normalement toutes les données disponibles, jusqu'au montant demandé, plutôt que d'attendre la réception du montant total demandé.

------------------------------------------------------------------------------------


#define _LARGEFILE64_SOURCE /* Voir feature_test_macros (7) */
#include <sys/types.h>
#include <unistd.h>

<!-- off64_t lseek64(int fd , off64_t offset , int d'où ); -->

Description
La famille de fonctions lseek (2) repositionne le décalage du fichier ouvert associé au descripteur de fichier fd pour décaler les octets par rapport au début, à la position actuelle ou à la fin du fichier, lorsque d'où a la valeur SEEK_SET , SEEK_CUR , ou SEEK_END , respectivement.

Pour plus de détails, la valeur de retour et les erreurs, voir lseek (2).

Quatre interfaces sont disponibles : lseek (2), lseek64 (), llseek (2) et l'appel système brut _llseek (2).

je cherche

Prototype:
    off_t lseek(int  fd , off_t  offset , int  d'où );
lseek (2) utilise le type off_t . Il s'agit d'un type signé 32 bits sur les architectures 32 bits, à moins que l'on ne compile avec
#définir _FILE_OFFSET_BITS 64
auquel cas il s'agit d'un type signé 64 bits.
lseek64

Prototype:
    off64_t lseek64(int  fd , off64_t  offset , int  d'où );
La routine de bibliothèque lseek64 () utilise un type 64 bits même lorsque off_t est un type 32 bits. Son prototype (et le type off64_t ) n'est disponible que lorsqu'on compile avec
#définir _LARGEFILE64_SOURCE
La fonction lseek64 () est disponible depuis la glibc 2.1, et est définie comme un alias pour llseek ().
Je cherche

Prototype:
    loff_t llseek(int  fd , loff_t  offset , int  d'où );
Le type loff_t est un type signé 64 bits. La routine de bibliothèque llseek () est disponible dans la libc5 et la glibc et fonctionne sans définition spéciale. Son prototype a été donné dans < unistd.h > avec la libc5, mais la glibc ne fournit pas de prototype. C'est mauvais, puisqu'un prototype est nécessaire. Les utilisateurs doivent ajouter le prototype ci-dessus, ou quelque chose d'équivalent, à leur propre source. Lorsque les utilisateurs se sont plaints de la perte de données causée par une mauvaise compilation de e2fsck (8), la glibc 2.1.3 a ajouté l'avertissement de temps de liaison
"la fonction `llseek' peut être dangereuse ; utilisez plutôt `lseek64'."
Cela rend cette fonction inutilisable si l'on souhaite une compilation sans avertissement.
_llseek

Toutes les fonctions ci-dessus sont implémentées en termes de cet appel système. Le prototype est :
    int _llseek(int  fd , off_t  offset_hi , off_t  offset_lo ,
                loff_t * résultat , int  d'où );

------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

<!-- int stat(const char * path , struct stat * buf );
int fstat(int fd , struct stat * buf );
int lstat(const char * path , struct stat * buf ); -->

Configuration requise pour les macros de test de fonctionnalité pour la glibc (voir feature_test_macros (7)) :

lstat () :
_BSD_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED
|| /* Depuis la glibc 2.10 : */ _POSIX_C_SOURCE >= 200112L
Description
Ces fonctions renvoient des informations sur un fichier. Aucune autorisation n'est requise sur le fichier lui-même, mais dans le cas de stat () et lstat () - une autorisation d'exécution (recherche) est requise sur tous les répertoires du chemin menant au fichier.

stat () stats le fichier pointé par path et remplit buf .

lstat () est identique à stat (), sauf que si path est un lien symbolique, alors le lien lui-même est stat-ed, pas le fichier auquel il se réfère.

fstat () est identique à stat (), sauf que le fichier à stat-ed est spécifié par le descripteur de fichier fd .

Tous ces appels système renvoient une structure de statistiques contenant les champs suivants :

<!-- structure stat {
    dev_t st_dev ; /* ID du périphérique contenant le fichier */
    ino_t st_ino; /* numéro d'inode */
    mode_t st_mode ; /* protection */
    nlink_t st_nlink ; /* nombre de liens durs */
    uid_t st_uid ; /* ID utilisateur du propriétaire */
    gid_t st_gid ; /* ID de groupe du propriétaire */
    dev_t st_rdev ; /* ID du périphérique (si fichier spécial) */
    off_t st_size ; /* taille totale, en octets */
    blksize_t st_blksize ; /* taille de bloc pour les E/S du système de fichiers */
    blkcnt_t st_blocks ; /* nombre de blocs 512B alloués */
    time_t st_atime ; /* heure du dernier accès */
    time_t st_mtime ; /* heure de la dernière modification */
    time_t st_ctime ; /* heure du dernier changement d'état */
} ; -->

Le champ st_dev décrit le périphérique sur lequel ce fichier réside. (Les macros majeures (3) et mineures (3) peuvent être utiles pour décomposer l'ID de périphérique dans ce champ.)
Le champ st_rdev décrit le périphérique représenté par ce fichier (inode).

Le champ st_size donne la taille du fichier (s'il s'agit d'un fichier normal ou d'un lien symbolique) en octets. La taille d'un lien symbolique est la longueur du nom de chemin qu'il contient, sans octet nul de fin.

Le champ st_blocks indique le nombre de blocs alloués au fichier, unités de 512 octets. (Cela peut être plus petit que st_size /512 lorsque le fichier a des trous.)

Le champ st_blksize donne la taille de bloc "préférée" pour une E/S efficace du système de fichiers. (L'écriture dans un fichier en petits morceaux peut entraîner une lecture-modification-réécriture inefficace.)

Tous les systèmes de fichiers Linux n'implémentent pas tous les champs de temps. Certains types de systèmes de fichiers autorisent le montage de manière à ce que les accès aux fichiers et/ou répertoires n'entraînent pas une mise à jour du champ st_atime . (Voir noatime , nodiratime et relatime dans mount (8) et les informations associées dans mount (2).) De plus, st_atime n'est pas mis à jour si un fichier est ouvert avec O_NOATIME ; voir ouvert (2).

Le champ st_atime est modifié par les accès au fichier, par exemple, par execve (2), mknod (2), pipe (2), utime (2) et read (2) (de plus de zéro octet). D'autres routines, comme mmap (2), peuvent ou non mettre à jour st_atime .

Le champ st_mtime est modifié par des modifications de fichiers, par exemple, par mknod (2), truncate (2), utime (2) et write (2) (de plus de zéro octet). De plus, st_mtime d'un répertoire est modifié par la création ou la suppression de fichiers dans ce répertoire. Le champ st_mtime n'est pas modifié pour les changements de propriétaire, de groupe, de nombre de liens physiques ou de mode.

Le champ st_ctime est modifié en écrivant ou en définissant les informations d'inode (c'est-à-dire le propriétaire, le groupe, le nombre de liens, le mode, etc.).

------------------------------------------------------------------------------------

#include <poll.h>

<!-- int poll(struct pollfd * fds , nfds_t  nfds , int  timeout ); -->

#define _GNU_SOURCE          /* Voir feature_test_macros (7) */
 #include < poll.h >

int ppoll(struct pollfd * fds , nfds_t  nfds ,
        const struct timespec * timeout_ts , const sigset_t * sigmask );
Description
poll () effectue une tâche similaire à select (2) : il attend que l'un des ensembles de descripteurs de fichiers soit prêt à effectuer des E/S.

L'ensemble de descripteurs de fichiers à surveiller est spécifié dans l' argument fds , qui est un tableau de structures de la forme suivante :

<!-- structure pollfd {
    int fd ; /* descripteur de fichier */
    événements courts; /* événements demandés */
    courts événements; /* événements renvoyés */
} ; -->

L'appelant doit spécifier le nombre d'éléments dans le tableau fds dans nfds .
Le champ fd contient un descripteur de fichier pour un fichier ouvert. Si ce champ est négatif, le champ événements correspondant est ignoré et le champ événements renvoie zéro. (Cela fournit un moyen facile d'ignorer un descripteur de fichier pour un seul appel poll () : annulez simplement le champ fd .)

Le champ events est un paramètre d'entrée, un masque binaire spécifiant les événements qui intéressent l'application pour le descripteur de fichier fd . Si ce champ est spécifié à zéro, tous les événements sont ignorés pour fd et revents renvoie zéro.

------------------------------------------------------------------------------------
