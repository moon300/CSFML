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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network/SocketSelector.h>
#include <SFML/Network/SocketSelectorStruct.h>
#include <SFML/Network/TcpListenerStruct.h>
#include <SFML/Network/TcpSocketStruct.h>
#include <SFML/Network/UdpSocketStruct.h>
#include <SFML/Internal.h>


////////////////////////////////////////////////////////////
sfSocketSelector* sfSocketSelector_Create(void)
{
    return new sfSocketSelector;
}


////////////////////////////////////////////////////////////
sfSocketSelector* sfSocketSelector_Copy(sfSocketSelector* selector)
{
    CSFML_CHECK_RETURN(selector, NULL);

    return new sfSocketSelector(*selector);
}


////////////////////////////////////////////////////////////
void sfSocketSelector_Destroy(sfSocketSelector* selector)
{
    delete selector;
}


////////////////////////////////////////////////////////////
void sfSocketSelector_AddTcpListener(sfSocketSelector* selector, sfTcpListener* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Add(socket->This));
}
void sfSocketSelector_AddTcpSocket(sfSocketSelector* selector, sfTcpSocket* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Add(socket->This));
}
void sfSocketSelector_AddUdpSocket(sfSocketSelector* selector, sfUdpSocket* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Add(socket->This));
}


////////////////////////////////////////////////////////////
void sfSocketSelector_RemoveTcpListener(sfSocketSelector* selector, sfTcpListener* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Remove(socket->This));
}
void sfSocketSelector_RemoveTcpSocket(sfSocketSelector* selector, sfTcpSocket* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Remove(socket->This));
}
void sfSocketSelector_RemoveUdpSocket(sfSocketSelector* selector, sfUdpSocket* socket)
{
    CSFML_CHECK(socket);
    CSFML_CALL(selector, Remove(socket->This));
}


////////////////////////////////////////////////////////////
void sfSocketSelector_Clear(sfSocketSelector* selector)
{
    CSFML_CALL(selector, Clear());
}


////////////////////////////////////////////////////////////
sfBool sfSocketSelector_Wait(sfSocketSelector* selector, sfUint32 timeout)
{
    CSFML_CALL_RETURN(selector, Wait(timeout), sfFalse);
}


////////////////////////////////////////////////////////////
sfBool sfSocketSelector_IsTcpListenerReady(const sfSocketSelector* selector, sfTcpListener* socket)
{
    CSFML_CHECK_RETURN(socket, sfFalse);
    CSFML_CALL_RETURN(selector, IsReady(socket->This), sfFalse);
}
sfBool sfSocketSelector_IsTcpSocketReady(const sfSocketSelector* selector, sfTcpSocket* socket)
{
    CSFML_CHECK_RETURN(socket, sfFalse);
    CSFML_CALL_RETURN(selector, IsReady(socket->This), sfFalse);
}
sfBool sfSocketSelector_IsUdpSocketReady(const sfSocketSelector* selector, sfUdpSocket* socket)
{
    CSFML_CHECK_RETURN(socket, sfFalse);
    CSFML_CALL_RETURN(selector, IsReady(socket->This), sfFalse);
}
