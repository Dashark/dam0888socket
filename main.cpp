
#include "ZLServer.h"

#include <glib.h>
#include <syslog.h>
#include <cassert>
#include <iostream>
#include "Messager.hpp"
#include "Device.h"

typedef struct _ApplicationState ApplicationState;
struct _ApplicationState {

  ZLServer *zls;
};
/* add callback into GLib Main Event Loop. */
void listenChannel (ApplicationState *state, int fd, GIOFunc func);
/* callback method for socket accept. */
gboolean socket_connecting (GIOChannel *channel, GIOCondition condition, gpointer *p);
/* callback method for socket accept. */
gboolean socket_communite (GIOChannel *channel, GIOCondition condition, ApplicationState *state);

/*timeout 调用函数*/
static gboolean
application_iterate(ZLServer *server);

#define ITERATION_PERIOD 150
static GMainLoop *loop;

/* ctrl+c 结束程序处理函数 */
static void close_sigint (int dummy)
{
  syslog (LOG_INFO, "Ctrl+c 终止进程...\n");

	g_main_loop_quit (loop); //Stops a GMainLoop from running.
}

int main(int argc, char *argv[]) {
  if(argc == 1) {
    Messager *mes = new AGVButtonMessager();
    mes->setID("shark");
    mes->setAStep("Unknown");
    mes->setTime("1999/08/03");
    mes->setKV("PowerOn", "ON");
    mes->dump();
    delete mes;
    std::cout << "damSocket timeout" << std::endl;
    return -1;
  }
	signal (SIGINT, close_sigint); //Ctrl+C结束程序运行处理函数
  openlog("dam0888Socket", LOG_PID|LOG_CONS|LOG_PERROR, LOG_USER);
  ApplicationState *state = new ApplicationState;

  DeviceFactory dfa;
  std::vector<Device*> devs = dfa.createDevices();

  ZLDefine zld;
  state->zls = zld.createServer();
  for(Device *dev : devs) {
    state->zls->attach(dev);
    dev->setServer(state->zls);
  }
  int fd = state->zls->listenZL();
  if(fd == -1) return -1;
	loop = g_main_loop_new (NULL, FALSE); //Creates a new GMainLoop structure.
  assert(loop != NULL);
  listenChannel(state, fd, (GIOFunc)socket_connecting);
  g_timeout_add(g_ascii_strtoull(argv[1], NULL, 10),
                (GSourceFunc)application_iterate, state->zls);

	g_main_loop_run (loop); //Runs a main loop until g_main_loop_quit() is called on the loop.

	g_main_loop_unref (loop); //Decreases the reference count on a GMainLoop object by one.
  delete state->zls;
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
 * callback method for socket accept.
-------------------------------------*/
gboolean socket_connecting (GIOChannel *channel, GIOCondition condition, gpointer *p)
{
	/* A client is asking a new connection */
	int newfd = -1;

	syslog (LOG_INFO, "socket_connecting... \n");
  ApplicationState *state = (ApplicationState*)p;
	/* Handle new connections */

  newfd = state->zls->clientConnected();
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

#if DEBUG
	int flags = fcntl (fd, F_GETFD);
	if ((flags & O_NONBLOCK) == O_NONBLOCK) {
    fprintf (stderr, "Yup, it's nonblocking.\n");
	} else {
    fprintf (stderr, "Nope, it's blocking.\n");
	}
#endif
  /*
	unsigned char recvMsg[64] = {0};

	int rc = recv (fd, recvMsg, 64, 0);

	if (rc > 0) {
	  for (int i = 0; i < rc; i++) {
		   fprintf (stderr, "[%02hhX]", recvMsg[i]);
	  }
	  fprintf (stderr, "\n");
	}
  else {
		fprintf (stderr, "recv failed !!\n");
		GSource *current_source;
		current_source = g_main_current_source ();
		fprintf (stderr, "destroy %s\n", g_source_get_name (current_source));
		g_source_destroy (current_source);

		return G_SOURCE_REMOVE;
    }*/

	return G_SOURCE_CONTINUE;
}

static gboolean
application_iterate(ZLServer *server) {
  assert(server != nullptr);
  server->readAll();
  /* The timer will continue to call this function every second as long as it
   * returns TRUE.
   */
  return TRUE;
}
