/** timeserv.c - a socket-based time of day server
 */

#include  <stdio.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <netdb.h>
#include  <time.h>
#include  <strings.h>

#define   PORTNUM  13000   /* our time service phone number */
#define   HOSTLEN  256
#define   oops(msg)      { perror(msg); exit(1); }


void print_ip(struct sockaddr *);

int main(int ac, char *av[])
{
    struct  sockaddr_in     saddr;      /* build our address here */
    struct  hostent         *hp;        /* this is part of our    */
    char    hostname[HOSTLEN];          /* address                */
    int     sock_id,sock_fd;            /* line id, file desc     */
    FILE    *sock_fp;                   /* use socket as stream   */
    char    *ctime();                   /* convert secs to string */
    time_t  thetime;                    /* the time we report     */

    /*
     * Step 1: ask kernel for a socket
     */

    sock_id = socket( PF_INET, SOCK_STREAM, 0 );    /* get a socket */
    if ( sock_id == -1 )
    oops( "socket" );

    /*
     * Step 2: bind address to socket.  Address is host,port
     */

    bzero( (void *)&saddr, sizeof(saddr) ); /* clear out struct     */

    gethostname( hostname, HOSTLEN );       /* where am I ?         */
    printf("My hostname is: %s\n", hostname);
    hp = gethostbyname( hostname );         /* get info about host  */
    printf("h_name: %s\n", hp->h_name);
    print_ip((struct sockaddr *)hp);
    saddr.sin_port = htons(PORTNUM);        /* fill in socket port  */
    saddr.sin_family = AF_INET ;            /* fill in addr family  */

    if ( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0 )
    oops( "bind" );

    /*
     * Step 3: allow incoming calls with Qsize=1 on socket
     */

    if ( listen(sock_id, 1) != 0 )
    oops( "listen" );

    /*
     * main loop: accept(), write(), close()
     */

    while ( 1 ){
        struct sockaddr caller_addr;
        socklen_t addr_len;
        sock_fd = accept(sock_id, &caller_addr, &addr_len); /* wait for call */
        print_ip(&caller_addr);
        printf("Wow! got a call!\n");
        if ( sock_fd == -1 )
        oops( "accept" );       /* error getting calls  */

        sock_fp = fdopen(sock_fd,"w");  /* we'll write to the   */
        if ( sock_fp == NULL )          /* socket as a stream   */
        oops( "fdopen" );       /* unless we can't      */

        thetime = time(NULL);           /* get time             */
        /* and convert to strng */
        fprintf( sock_fp, "The time here is .." );
        fprintf( sock_fp, "%s", ctime(&thetime) );
        fclose( sock_fp );              /* release connection   */
    }
}

void print_ip(struct sockaddr *res)
/**
 *
 * @ref https://stackoverflow.com/questions/1276294/getting-ipv4-address-from-a-sockaddr-structure
 * @param addr_in
 */
{
    char *s = NULL;
    switch(res->sa_family) {
        case AF_INET: {
            struct sockaddr_in *addr_in = (struct sockaddr_in *)res;
            s = malloc(INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(addr_in->sin_addr), s, INET_ADDRSTRLEN);
            break;
        }
        case AF_INET6: {
            struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6 *)res;
            s = malloc(INET6_ADDRSTRLEN);
            inet_ntop(AF_INET6, &(addr_in6->sin6_addr), s, INET6_ADDRSTRLEN);
            break;
        }
        default:
            printf("UNKNOWN sa_family\n");
            break;
    }
    printf("IP address: %s\n", s);
    free(s);
}