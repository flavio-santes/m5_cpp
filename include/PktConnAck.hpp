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

#ifndef __PKT_CONNACK_HPP__
#define __PKT_CONNACK_HPP__

#include "AppBuf.hpp"
#include "Common.hpp"
#include "Packet.hpp"
#include "Properties.hpp"

namespace m5
{

class PktConnAck : public Packet
{
private:
    bool _sessionPresent = false;
    uint8_t _reasonCode  = (uint8_t)ReasonCode::SUCCESS;

    enum StatusCode writeVariableHeader(AppBuf &buf) override;
    enum StatusCode writePayload(AppBuf &buf) override;

    enum StatusCode readVariableHeader(AppBuf &buf) override;
    enum StatusCode readPayload(AppBuf &buf) override;

public:
    PktConnAck(bool sessionPresent   = false,
               ReasonCode reasonCode = ReasonCode::SUCCESS);
    PktConnAck(AppBuf &buf);
    ~PktConnAck()
    {
    }

    enum StatusCode assignedClientIdentifier(const uint8_t *data,
                                             uint16_t size);
    enum StatusCode assignedClientIdentifier(const char *str);
    const ByteArray &assignedClientIdentifier(void) const;

    enum StatusCode serverKeepAlive(uint16_t v);
    uint16_t serverKeepAlive(void) const;

    enum StatusCode authenticationMethod(const uint8_t *data, uint16_t size);
    enum StatusCode authenticationMethod(const char *str);
    const ByteArray &authenticationMethod(void) const;

    enum StatusCode authenticationData(const uint8_t *data, uint16_t size);
    const ByteArray &authenticationData(void) const;

    enum StatusCode responseInformation(const uint8_t *data, uint16_t size);
    enum StatusCode responseInformation(const char *str);
    const ByteArray &responseInformation(void) const;

    enum StatusCode serverReference(const uint8_t *data, uint16_t size);
    enum StatusCode serverReference(const char *str);
    const ByteArray &serverReference(void) const;

    enum StatusCode reasonString(const uint8_t *data, uint16_t size);
    enum StatusCode reasonString(const char *str);
    const ByteArray &reasonString(void) const;

    enum StatusCode receiveMaximum(uint16_t v);
    uint16_t receiveMaximum(void) const;

    enum StatusCode topicAliasMaximum(uint16_t v);
    uint16_t topicAliasMaximum(void) const;

    enum StatusCode maximumQoS(enum PktQoS qos);
    enum PktQoS maximumQoS(void) const;

    enum StatusCode retainAvailable(bool v);
    bool retainAvailable(void) const;

    enum StatusCode userProperty(const uint8_t *key, uint16_t keySize,
                                 const uint8_t *value, uint16_t valueSize);
    enum StatusCode userProperty(const char *key, const char *val);
    const UserProperty &userProperty(void) const;

    enum StatusCode maximumPacketSize(uint32_t v);
    uint32_t maximumPacketSize(void) const;

    enum StatusCode wildcardSubscriptionAvailable(bool v);
    bool wildcardSubscriptionAvailable(void) const;

    enum StatusCode subscriptionIdentifierAvailable(bool v);
    bool subscriptionIdentifierAvailable(void) const;

    enum StatusCode sharedSubscriptionAvailable(bool v);
    bool sharedSubscriptionAvailable(void) const;

    uint32_t writeTo(AppBuf &buf) override;
    uint32_t readFrom(AppBuf &buf) override;
};
}

#endif
