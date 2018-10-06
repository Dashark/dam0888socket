
#include "ZLServer.h"

#include <glib.h>
#include <syslog.h>
typedef struct _ApplicationState ApplicationState;
struct _ApplicationState {
  GMainContext *ctx;
  ZLServer *zls;
};
/* add callback into GLib Main Event Loop. */
void listenChannel (ApplicationState *state, int fd, GSourceFunc func);
/* callback method for socket accept. */
gboolean socket_connecting (ApplicationState *state);
/* callback method for socket accept. */
gboolean socket_communite (ApplicationState *state);

/*timeout 调用函数*/
static gboolean
application_iterate(ZLServer *server);

#define ITERATION_PERIOD 50
static GMainLoop *loop;

/* ctrl+c 结束程序处理函数 */
static void close_sigint (int dummy)
{
  syslog (LOG_INFO, "Ctrl+c 终止进程...\n");

	g_main_loop_quit (loop); //Stops a GMainLoop from running. 
}

int main() {
	signal (SIGINT, close_sigint); //Ctrl+C结束程序运行处理函数
  openlog("dam0888Socket", LOG_PID|LOG_CONS|LOG_PERROR, LOG_USER);
  ApplicationState state;
  state.ctx = g_main_context_new();

  ZLDefine zld;
  state.zls = zld.createServer();
  int fd = state.zls->listenZL();
  listenChannel(&state, fd, (GSourceFunc)socket_connecting);
  g_timeout_add(ITERATION_PERIOD,
                (GSourceFunc)application_iterate, state.zls);
	loop = g_main_loop_new (state.ctx, FALSE); //Creates a new GMainLoop structure.
	g_main_loop_run (loop); //Runs a main loop until g_main_loop_quit() is called on the loop.

	g_main_loop_unref (loop); //Decreases the reference count on a GMainLoop object by one. 
	g_main_context_unref (state.ctx); //Decreases the reference count on a GMainContext object by one.
  delete state.zls;
  return 0;
}

/*-----------------------------------------
 * add callback into GLib Main Event Loop.
-----------------------------------------*/
void listenChannel (ApplicationState *state, int fd, GSourceFunc func) 
{
	GIOChannel *channel;
	GSource *source;
	char name[20] = {0};

	channel = g_io_channel_unix_new (fd); //To create a new GIOChannel on Unix systems
	source = g_io_create_watch (channel, G_IO_IN); //Creates a GSource that's dispatched when condition is met for the given channel.

	sprintf (name, "source'fd = %d", fd);
	g_source_set_name (source, name); //Sets a name for the source, test ***

	g_source_set_callback (source, func, state, NULL); //Sets the callback function for a source.
	g_source_attach (source, state->ctx); //attach source to context (g_ctx)

	/*the loop has an internal reference so we'll drop ours*/
	g_io_channel_unref (channel); //Decrements the reference count of a GIOChannel.
	g_source_unref (source); //Decreases the reference count of a source by one.
}

/*-------------------------------------
 * callback method for socket accept.
-------------------------------------*/
gboolean socket_connecting (ApplicationState *state) 
{
	/* A client is asking a new connection */
	int newfd = -1;

	syslog (LOG_INFO, "socket_connecting... \n"); 

	/* Handle new connections */
  newfd = state->zls->clientConnected();
	if (newfd == -1) {
		syslog(LOG_ERR, "Server accept error");
	} else {
		listenChannel (state, newfd, (GSourceFunc)socket_communite); //添加回调函数 socket_communite()
	}

	return G_SOURCE_CONTINUE;
}


/*-----------------------------------------
 * callback method for socket accept.
-----------------------------------------*/
gboolean socket_communite (ApplicationState *state) 
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
  server->readAll();
  /* The timer will continue to call this function every second as long as it
   * returns TRUE.
   */
  return TRUE;
}
