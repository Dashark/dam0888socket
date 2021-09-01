
#include "H3CServer.h"

#include <glib.h>
#include <syslog.h>
#include <cassert>
#include <iostream>

typedef struct _ApplicationState ApplicationState;
struct _ApplicationState {

  H3CServer *h3cs;
  H3CDefine *h3cd;
};
/* add callback into GLib Main Event Loop. */
void listenChannel (ApplicationState *state, int fd, GIOFunc func);
/* callback method for socket accept. */
gboolean socket_connecting (GIOChannel *channel, GIOCondition condition, gpointer *p);
/* callback method for socket accept. */
gboolean socket_communite (GIOChannel *channel, GIOCondition condition, ApplicationState *state);

/*timeout 调用函数*/
static gboolean
application_iterate(H3CDefine *server);

#define ITERATION_PERIOD 150
static GMainLoop *loop;

/* ctrl+c 结束程序处理函数 */
static void close_sigint (int dummy)
{
  syslog (LOG_INFO, "Ctrl+c terminate process...\n");

	g_main_loop_quit (loop); //Stops a GMainLoop from running. 
}

int main(int argc, char *argv[]) {
  /*
  if(argc == 1) {
    std::cout << "damSocket timeout" << std::endl;
    return -1;
  }
  */
  signal (SIGINT, close_sigint); //Ctrl+C结束程序运行处理函数
  openlog("H3CSocket", LOG_PID|LOG_CONS|LOG_PERROR, LOG_USER);
  ApplicationState *state = new ApplicationState;

  state->h3cd = new H3CDefine();
  state->h3cs = state->h3cd->createServer();
  state->h3cd->initH3C(state->h3cs);
  state->h3cd->loginH3C();
  state->h3cd->alarmH3C();

  int fd = state->h3cs->listenH3C();
  if(fd == -1) return -1;

  loop = g_main_loop_new (NULL, FALSE); //Creates a new GMainLoop structure.  
  assert(loop != NULL);
  listenChannel(state, fd, (GIOFunc)socket_connecting);
  g_timeout_add_seconds(10, (GSourceFunc)application_iterate, state->h3cd);

  g_main_loop_run (loop); //Runs a main loop until g_main_loop_quit() is called on the loop.
  syslog(LOG_INFO, "LOOP quit!!!");
  g_main_loop_unref (loop); //Decreases the reference count on a GMainLoop object by one. 
  delete state->h3cd;
  delete state->h3cs;
  delete state;
  return 0;
}

/*-----------------------------------------
 * add callback into GLib Main Event Loop.
-----------------------------------------*/
void listenChannel (ApplicationState *state, int fd, GIOFunc func) 
{
	GIOChannel *channel;

	channel = g_io_channel_unix_new (fd); //To create a new GIOChannel on Unix systems
	g_io_add_watch (channel, G_IO_IN, func, state); //Creates a GSource that's dispatched when condition is met for the given channel.

	/*the loop has an internal reference so we'll drop ours*/
	g_io_channel_unref (channel); //Decrements the reference count of a GIOChannel.
}

/*-------------------------------------
 * callback method for socket accept.  By Java client
-------------------------------------*/
gboolean socket_connecting (GIOChannel *channel, GIOCondition condition, gpointer *p) 
{
	/* A client is asking a new connection */
	int newfd = -1;

	syslog (LOG_INFO, "socket_connecting... \n"); 
  ApplicationState *state = (ApplicationState*)p;
	/* Handle new connections */

  newfd = state->h3cs->clientConnected();
	if (newfd == -1) {
		syslog(LOG_ERR, "Server accept error");
    return G_SOURCE_REMOVE;
	} else {
		listenChannel (state, newfd, (GIOFunc)socket_communite); //添加回调函数 socket_communite()
	}

	return G_SOURCE_CONTINUE;
}


/*-----------------------------------------
 * callback method for socket accept.
-----------------------------------------*/
gboolean socket_communite (GIOChannel *channel, GIOCondition condition, ApplicationState *state) 
{
  syslog (LOG_INFO, "socket_communite func !!!\n");

  if (G_IO_IN != condition) {
    syslog (LOG_WARNING, "socket_communite condition error!!!\n");
  }
  gchar *output; gsize len = 0;
  g_io_channel_read_to_end(channel, &output, &len, NULL);
  if (0 != len) {
    output[len-1] = 0;
    syslog (LOG_INFO, "socket_communite info %s!!!\n", output);
    g_free(output);
  } else {
    state->h3cs->closeClientModel(g_io_channel_unix_get_fd(channel));
    g_io_channel_unref(channel);
    g_io_channel_shutdown(channel, TRUE, NULL);
  }

#if DEBUG
    int flags = fcntl (fd, F_GETFD);
    if ((flags & O_NONBLOCK) == O_NONBLOCK) {
      fprintf (stderr, "Yup, it's nonblocking.\n");
    } else {
      fprintf (stderr, "Nope, it's blocking.\n");
    }
#endif

	return G_SOURCE_CONTINUE;
}

static gboolean
application_iterate(H3CDefine *h3cd) {
  assert(h3cd != nullptr);
  h3cd->loginH3C();
  h3cd->alarmH3C();
  /* The timer will continue to call this function every second as long as it
   * returns TRUE.
   */
  return TRUE;
}
