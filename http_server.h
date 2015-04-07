#include "stdafx.h"
#include "http_request.h"

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_
/*
 *  v   ������� HTTP-������.
 *  v   ������ ����� make.
 *  v   ������:  ./wwwd -d <dir> -h <ip> -p <port>
 *  +   ���������� HEAD/GET/POST.
 *  v   ������� 200 � 404
 *  v   � �������� <dir> - html � jpeg �����
 *
 *  8 ������ (����������)
 */
//-----------------------------------------
#define STR_IP_LEN 16
typedef struct http_server_config srv_conf;
struct  http_server_config
{
  uint16_t  port;
  char      ip[STR_IP_LEN];
  char     *path;
 };
//-----------------------------------------
int   http_server_config_init  (srv_conf *conf, char *path, char *port, char *ip);
void  http_server_config_print (srv_conf *conf, FILE *stream);
void  http_server_config_free  (srv_conf *conf);
//-----------------------------------------
int   parse_console_parameters (int argc, char **argv, srv_conf *conf);
//-----------------------------------------
int   set_nonblock (evutil_socket_t fd);
//-----------------------------------------
struct client
{
  /* bufferevent already has separate
   * two buffers for input and output.
   */
  struct bufferevent     *b_ev;
  struct event_base      *base;
  struct evbuffer      *buffer;
  struct http_request  request;
};
//-----------------------------------------
// void  http_ac_err_cb (struct evconnlistener *listener, void *arg);
// void  http_accept_cb (struct evconnlistener *listener, evutil_socket_t fd,
//                       struct sockaddr *address, int socklen, void *arg);
void  http_accept_cb (evutil_socket_t fd, short ev, void *arg);
void  http_ac_err_cb (evutil_socket_t fd, short ev, void *arg);
//-----------------------------------------
void  http_read_cb   (struct bufferevent *b_ev, void *arg);
void  http_write_cb  (struct bufferevent *b_ev, void *arg);
void  http_error_cb  (struct bufferevent *b_ev, short events, void *arg);
//-----------------------------------------
#endif // _HTTP_SERVER_H_
