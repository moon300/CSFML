////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_HTTP_H
#define SFML_HTTP_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.h>
#include <SFML/Network/Types.h>


////////////////////////////////////////////////////////////
/// \brief Enumerate the available HTTP methods for a request
///
////////////////////////////////////////////////////////////
enum sfHttpMethod
{
    sfHttpGet,  ///< Request in get mode, standard method to retrieve a page
    sfHttpPost, ///< Request in post mode, usually to send data to a page
    sfHttpHead  ///< Request a page's header only
};


////////////////////////////////////////////////////////////
/// \brief Enumerate all the valid status codes for a response
///
////////////////////////////////////////////////////////////
enum sfHttpStatus
{
    // 2xx: success
    sfHttpOk        = 200, ///< Most common code returned when operation was successful
    sfHttpCreated   = 201, ///< The resource has successfully been created
    sfHttpAccepted  = 202, ///< The request has been accepted, but will be processed later by the server
    sfHttpNoContent = 204, ///< Sent when the server didn't send any data in return

    // 3xx: redirection
    sfHttpMultipleChoices  = 300, ///< The requested page can be accessed from several locations
    sfHttpMovedPermanently = 301, ///< The requested page has permanently moved to a new location
    sfHttpMovedTemporarily = 302, ///< The requested page has temporarily moved to a new location
    sfHttpNotModified      = 304, ///< For conditionnal requests, means the requested page hasn't changed and doesn't need to be refreshed

    // 4xx: client error
    sfHttpBadRequest   = 400, ///< The server couldn't understand the request (syntax error)
    sfHttpUnauthorized = 401, ///< The requested page needs an authentification to be accessed
    sfHttpForbidden    = 403, ///< The requested page cannot be accessed at all, even with authentification
    sfHttpNotFound     = 404, ///< The requested page doesn't exist

    // 5xx: server error
    sfHttpInternalServerError = 500, ///< The server encountered an unexpected error
    sfHttpNotImplemented      = 501, ///< The server doesn't implement a requested feature
    sfHttpBadGateway          = 502, ///< The gateway server has received an error from the source server
    sfHttpServiceNotAvailable = 503, ///< The server is temporarily unavailable (overloaded, in maintenance, ...)

    // 10xx: SFML custom codes
    sfHttpInvalidResponse  = 1000, ///< Response is not a valid HTTP one
    sfHttpConnectionFailed = 1001  ///< Connection with server failed
};


////////////////////////////////////////////////////////////
/// \brief Create a new HTTP request
///
/// \return A new sfHttpRequest object
///
////////////////////////////////////////////////////////////
CSFML_API sfHttpRequest* sfHttpRequest_Create(void);

////////////////////////////////////////////////////////////
/// \brief Destroy a HTTP request
///
/// \param httpRequest HTTP request to destroy
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_Destroy(sfHttpRequest* httpRequest);

////////////////////////////////////////////////////////////
/// \brief Set the value of a header field of a HTTP request
///
/// The field is created if it doesn't exist. The name of
/// the field is case insensitive.
/// By default, a request doesn't contain any field (but the
/// mandatory fields are added later by the HTTP client when
/// sending the request).
///
/// \param httpRequest HTTP request
/// \param field       Name of the field to set
/// \param value       Value of the field
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_SetField(sfHttpRequest* httpRequest, const char* field, const char* value);

////////////////////////////////////////////////////////////
/// \brief Set a HTTP request method
///
/// See the sfHttpMethod enumeration for a complete list of all
/// the availale methods.
/// The method is sfHttpGet by default.
///
/// \param httpRequest HTTP request
/// \param method      Method to use for the request
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_SetMethod(sfHttpRequest* httpRequest, sfHttpMethod method);

////////////////////////////////////////////////////////////
/// \brief Set a HTTP request URI
///
/// The URI is the resource (usually a web page or a file)
/// that you want to get or post.
/// The URI is "/" (the root page) by default.
///
/// \param httpRequest HTTP request
/// \param uri         URI to request, relative to the host
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_SetUri(sfHttpRequest* httpRequest, const char* uri);

////////////////////////////////////////////////////////////
/// \brief Set the HTTP version of a HTTP request
///
/// The HTTP version is 1.0 by default.
///
/// \param httpRequest HTTP request
/// \param major       Major HTTP version number
/// \param minor       Minor HTTP version number
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_SetHttpVersion(sfHttpRequest* httpRequest, unsigned int major, unsigned int minor);

////////////////////////////////////////////////////////////
/// \brief Set the body of a HTTP request
///
/// The body of a request is optional and only makes sense
/// for POST requests. It is ignored for all other methods.
/// The body is empty by default.
///
/// \param httpRequest HTTP request
/// \param body        Content of the body
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpRequest_SetBody(sfHttpRequest* httpRequest, const char* body);

////////////////////////////////////////////////////////////
/// \brief Destroy a HTTP response
///
/// \param httpResponse HTTP response to destroy
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttpResponse_Destroy(sfHttpResponse* httpResponse);

////////////////////////////////////////////////////////////
/// \brief Get the value of a field of a HTTP response
///
/// If the field \a field is not found in the response header,
/// the empty string is returned. This function uses
/// case-insensitive comparisons.
///
/// \param httpResponse HTTP response
/// \param field        Name of the field to get
///
/// \return Value of the field, or empty string if not found
///
////////////////////////////////////////////////////////////
CSFML_API const char* sfHttpResponse_GetField(const sfHttpResponse* httpResponse, const char* field);

////////////////////////////////////////////////////////////
/// \brief Get the status code of a HTTP reponse
///
/// The status code should be the first thing to be checked
/// after receiving a response, it defines whether it is a
/// success, a failure or anything else (see the sfHttpStatus
/// enumeration).
///
/// \param httpResponse HTTP response
///
/// \return Status code of the response
///
////////////////////////////////////////////////////////////
CSFML_API sfHttpStatus sfHttpResponse_GetStatus(const sfHttpResponse* httpResponse);

////////////////////////////////////////////////////////////
/// \brief Get the major HTTP version number of a HTTP response
///
/// \param httpResponse HTTP response
///
/// \return Major HTTP version number
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfHttpResponse_GetMajorVersion(const sfHttpResponse* httpResponse);

////////////////////////////////////////////////////////////
/// \brief Get the minor HTTP version number of a HTTP response
///
/// \param httpResponse HTTP response
///
/// \return Minor HTTP version number
///
////////////////////////////////////////////////////////////
CSFML_API unsigned int sfHttpResponse_GetMinorVersion(const sfHttpResponse* httpResponse);

////////////////////////////////////////////////////////////
/// \brief Get the body of a HTTP response
///
/// The body of a response may contain:
/// \li the requested page (for GET requests)
/// \li a response from the server (for POST requests)
/// \li nothing (for HEAD requests)
/// \li an error message (in case of an error)
///
/// \param httpResponse HTTP response
///
/// \return The response body
///
////////////////////////////////////////////////////////////
CSFML_API const char* sfHttpResponse_GetBody(const sfHttpResponse* httpResponse);

////////////////////////////////////////////////////////////
/// \brief Create a new Http object
///
/// \return A new sfHttp object
///
////////////////////////////////////////////////////////////
CSFML_API sfHttp* sfHttp_Create(void);

////////////////////////////////////////////////////////////
/// \brief Destroy a Http object
///
/// \param http Http object to destroy
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttp_Destroy(sfHttp* http);

////////////////////////////////////////////////////////////
/// \brief Set the target host of a HTTP object
///
/// This function just stores the host address and port, it
/// doesn't actually connect to it until you send a request.
/// If the port is 0, it means that the HTTP client will use
/// the right port according to the protocol used
/// (80 for HTTP, 443 for HTTPS). You should
/// leave it like this unless you really need a port other
/// than the standard one, or use an unknown protocol.
///
/// \param http Http object
/// \param host Web server to connect to
/// \param port Port to use for connection
///
////////////////////////////////////////////////////////////
CSFML_API void sfHttp_SetHost(sfHttp* http, const char* host, unsigned short port);

////////////////////////////////////////////////////////////
/// \brief Send a HTTP request and return the server's response.
///
/// You must have a valid host before sending a request (see sfHttp_SetHost).
/// Any missing mandatory header field in the request will be added
/// with an appropriate value.
/// Warning: this function waits for the server's response and may
/// not return instantly; use a thread if you don't want to block your
/// application, or use a timeout to limit the time to wait. A value
/// of 0 means that the client will use the system defaut timeout
/// (which is usually pretty long).
///
/// \param http    Http object
/// \param request Request to send
/// \param timeout Maximum time to wait, in milliseconds
///
/// \return Server's response
///
////////////////////////////////////////////////////////////
CSFML_API sfHttpResponse* sfHttp_SendRequest(sfHttp* http, const sfHttpRequest* request, sfUint32 timeout);


#endif // SFML_HTTP_H
