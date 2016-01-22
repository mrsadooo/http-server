#ifndef ERROR_H
#define ERROR_H

void HttpResponse(int * socket, int status, char * content);
void Http404Error(char * url, int * socket);

#endif