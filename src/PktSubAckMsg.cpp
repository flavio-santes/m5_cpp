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
 * Copyright (C) 2017 1byt3, customers at 1byt3.com
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

#include "PktSubAckMsg.hpp"

namespace m5
{

PktSubAckMsg::PktSubAckMsg(enum PktType type) : Packet(type, 0x00)
{
}

PktSubAckMsg::PktSubAckMsg(enum PktType type, AppBuf &buf) : Packet(type, 0x00)
{
    this->readFrom(buf);
}

enum StatusCode PktSubAckMsg::reasonString(const uint8_t *data, uint16_t size)
{
    return properties.reasonString(data, size);
}

enum StatusCode PktSubAckMsg::reasonString(const char *str)
{
    return properties.reasonString(str);
}

const ByteArray &PktSubAckMsg::reasonString(void) const
{
    return properties.reasonString();
}

enum StatusCode PktSubAckMsg::userProperty(const uint8_t *key, uint16_t keySize,
                                           const uint8_t *value,
                                           uint16_t valueSize)
{
    return properties.userProperty(key, keySize, value, valueSize);
}

enum StatusCode PktSubAckMsg::userProperty(const char *key, const char *val)
{
    return properties.userProperty(key, val);
}

const UserProperty &PktSubAckMsg::userProperty(void) const
{
    return properties.userProperty();
}

enum StatusCode PktSubAckMsg::writeVariableHeader(AppBuf &buf)
{
    buf.writeNum16(this->packetId());

    return properties.write(buf);
}

enum StatusCode PktSubAckMsg::writePayload(AppBuf &buf)
{
    for (auto it = _reasonCodes.begin(); it != _reasonCodes.end(); it++) {
        buf.writeNum8(*it);
    }

    return StatusCode::SUCCESS;
}

uint32_t PktSubAckMsg::writeTo(AppBuf &buf)
{
    Packet::payloadSize        = _reasonCodes.size();
    Packet::variableHeaderSize = 2;
    Packet::hasProperties      = true;

    return Packet::writeTo(buf);
}

enum StatusCode PktSubAckMsg::readVariableHeader(AppBuf &buf)
{
    this->packetId(buf.readNum16());
    if (this->packetId() == 0) {
        return StatusCode::INVALID_PACKET_ID;
    }

    return properties.read(buf);
}

enum StatusCode PktSubAckMsg::readPayload(AppBuf &buf)
{
    for (uint32_t i = 0; i < payloadSize; i++) {
        this->append((enum ReasonCode)buf.readNum8());
    }

    return StatusCode::SUCCESS;
}

uint32_t PktSubAckMsg::readFrom(AppBuf &buf)
{
    Packet::minRemLen = packetIdSize + propertyMinSize + reasonCodeSize;

    return Packet::readFrom(buf);
}
}
