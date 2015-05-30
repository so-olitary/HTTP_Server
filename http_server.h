﻿#include "stdafx.h"
#include "http_request.h"

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_
/*
 *  v   Создать HTTP-сервер.
 *  v   Сборка через make.
 *  v   Запуск:  ./wwwd -d/--dir <dir> -h/--ip <ip> -p/--port <port> -w/--workers <num>
 *  v   Реализация HEAD/GET/POST
 *  v   Статусы 200 и 404
 *  v   В каталоге <dir> - html и jpeg файлы
 */
//-----------------------------------------
#define  HTTP_SERVER_NAME  "http-server-hw"
#define  HTTP_IPSTRLENGTH  16U
#define  HTTP_MAX_WORKERS  16U

typedef struct http_server_config  srv_conf;
struct  http_server_config
{
  uint16_t   workers;
  uint16_t   port;
  char       ip[HTTP_IPSTRLENGTH];
  //-----------------------
  /* defines FILENAME_MAX in <stdio.h> */
  char  folder_path[FILENAME_MAX];
  char  server_path[FILENAME_MAX];
  //-----------------------
  char *ptr_server_name;
  //-----------------------
 };
extern struct http_server_config  server_conf;
//-----------------------------------------
int   http_server_config_init  (srv_conf *conf, char *path, char *port, char *ip, char* workers);
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
  //---------------------------
  struct http_request  request;
};
//-----------------------------------------
void  http_accept_cb (evutil_socket_t fd, short ev, void *arg);
void  http_ac_err_cb (evutil_socket_t fd, short ev, void *arg);
//-----------------------------------------
void  http_read_cb   (struct bufferevent *b_ev, void *arg);
void  http_error_cb  (struct bufferevent *b_ev, short events, void *arg);
//-----------------------------------------
#endif // _HTTP_SERVER_H_
