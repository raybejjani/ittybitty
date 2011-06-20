/*
 * HTTP Dispatcher public API
 */

#ifndef __HTTP_UTIL_H__
#define __HTTP_UTIL_H__

/*
 * Send a HTTP 1.0 400 response on sockfd.
 */
ssize_t itty_http_400(int sockfd);

/*
 * Send a HTTP 1.0 404 response on sockfd.
 */
ssize_t itty_http_404(int sockfd);

/*
 * Send a HTTP 1.0 200 response with data as the content.
 */
ssize_t itty_http_200(int sockfd, const char* data, int data_len);

#endif /* __HTTP_UTIL_H__ */

