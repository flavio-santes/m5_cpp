/*
 *                                   1byt3
 *
 *                              License Notice
 *
 * 1byt3 provides a commercial license agreement for this software. This
 * commercial license can be used for development of proprietary/commercial
 * software. Under this commercial license you do not need to comply with the
 * terms of the GNU Affero General Public License, either version 3 of the
 * License, or (at your option) any later version.
 *
 * If you don't receive a commercial license from us (1byt3), you MUST assume
 * that this software is distributed under the GNU Affero General Public
 * License, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Contact us for additional information: customers at 1byt3.com
 *
 *                          End of License Notice
 */

/*
 * MQTT 5 Low Level Packet Library
 *
 * Copyright (C) 2017, 2018 1byt3, customers at 1byt3.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PktPing.hpp"

namespace m5
{

PktPing::PktPing(enum PktType type) : Packet(type, 0x00)
{
}

PktPing::PktPing(enum PktType type, AppBuf &buf) : Packet(type, 0x00)
{
    this->readFrom(buf);
}

enum StatusCode PktPing::writeVariableHeader(AppBuf &buf)
{
    (void)buf;

    return StatusCode::SUCCESS;
}

enum StatusCode PktPing::writePayload(AppBuf &buf)
{
    (void)buf;

    return StatusCode::SUCCESS;
}

uint32_t PktPing::writeTo(AppBuf &buf)
{
    Packet::variableHeaderSize = 0;
    Packet::hasProperties      = false;

    return Packet::writeTo(buf);
}

enum StatusCode PktPing::readVariableHeader(AppBuf &buf)
{
    (void)buf;

    return StatusCode::SUCCESS;
}

enum StatusCode PktPing::readPayload(AppBuf &buf)
{
    (void)buf;

    return StatusCode::SUCCESS;
}

uint32_t PktPing::readFrom(AppBuf &buf)
{
    Packet::minRemLen = 0;

    return Packet::readFrom(buf);
}
}
