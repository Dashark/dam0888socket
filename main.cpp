
#include "ZLServer.h"

#include <glib.h>

/* add callback into GLib Main Event Loop. */
void listenChannel (int fd, GSourceFunc func);
/* callback method for socket accept. */
gboolean socket_connecting (GIOChannel *channel);
/* callback method for socket accept. */
gboolean socket_communite (GIOChannel *channel);

/*timeout 调用函数*/
static gboolean
application_iterate(ZLServer *server);

#define ITERATION_PERIOD 50

int main() {
  guint timer_source_id;
  ZLServer *zls = new ZLServer(port);
  int fd = zls->listen();
  listenChannel(fd, (GSourceFunc)socket_connecting);
  timer_source_id = g_timeout_add(ITERATION_PERIOD,
                                  (GSourceFunc)application_iterate, zls);
  return 0;
}

/*-----------------------------------------
 * add callback into GLib Main Event Loop.
-----------------------------------------*/
void listenChannel (int fd, GSourceFunc func) 
{
	GIOChannel *channel;
	GSource *source;
	char name[20] = {0};

	channel = g_io_channel_unix_new (fd); //To create a new GIOChannel on Unix systems
	source = g_io_create_watch (channel, G_IO_IN); //Creates a GSource that's dispatched when condition is met for the given channel.

	sprintf (name, "source'fd = %d", fd);
	g_source_set_name (source, name); //Sets a name for the source, test ***

	g_source_set_callback (source, func, channel, NULL); //Sets the callback function for a source.
	g_source_attach (source, g_ctx); //attach source to context (g_ctx)

	/*the loop has an internal reference so we'll drop ours*/
	g_io_channel_unref (channel); //Decrements the reference count of a GIOChannel.
	g_source_unref (source); //Decreases the reference count of a source by one.
}

/*-------------------------------------
 * callback method for socket accept.
-------------------------------------*/
gboolean socket_connecting (GIOChannel *channel) 
{
	/* A client is asking a new connection */
	struct sockaddr_in client; 
	socklen_t len = sizeof (client); 
	memset (&client, 0, sizeof (client)); 

	int fd = -1, newfd = -1;

	fprintf (stderr,"socket_connecting... \n"); 

	/* Handle new connections */
	fd = g_io_channel_unix_get_fd (channel); //返回GIOChannel的文件描述符
	newfd = accept (fd, (struct sockaddr*)&client, &len);
	zlmcu_newfd = newfd;
	if (newfd == -1) {
		perror ("Server accept error");
	} else {
		fprintf (stderr, "fd = %d, New connection from %s:%d on socket %d\n",
				fd, inet_ntoa(client.sin_addr), client.sin_port, newfd);
		modbus_set_socket (modbus_ctx, newfd); //设置modbus的文件描述编号
		listenChannel (newfd, (GSourceFunc)socket_communite); //添加回调函数 socket_communite()
	}

	return G_SOURCE_CONTINUE;
}


/*-----------------------------------------
 * callback method for socket accept.
-----------------------------------------*/
gboolean socket_communite (GIOChannel *channel) 
{
	fprintf (stderr, "socket_communite func !!!\n");
	int fd = g_io_channel_unix_get_fd (channel); //返回GIOChannel的文件描述符
	if (fd == -1) {
	  perror ("cannot accept client:");
	}

	#if 0
	int flags = fcntl (fd, F_GETFD);
	if ((flags & O_NONBLOCK) == O_NONBLOCK) {
	fprintf (stderr, "Yup, it's nonblocking.\n");
	} else {
	fprintf (stderr, "Nope, it's blocking.\n");
	}
	#endif

	unsigned char recvMsg[64] = {0};

	int rc = recv (fd, recvMsg, 64, 0);

	if (rc > 0) {
	  for (int i = 0; i < rc; i++) {
		   fprintf (stderr, "[%02hhX]", recvMsg[i]);
	  }
	  fprintf (stderr, "\n");
	} else {
		fprintf (stderr, "recv failed !!\n");
		GSource *current_source;
		current_source = g_main_current_source ();
		fprintf (stderr, "destroy %s\n", g_source_get_name (current_source));
		g_source_destroy (current_source);

		return G_SOURCE_REMOVE;
	}

	return G_SOURCE_CONTINUE;
}

static gboolean
application_iterate(ZLServer *server) {
  server->retrieve();
  /* The timer will continue to call this function every second as long as it
   * returns TRUE.
   */
  return TRUE;
}
