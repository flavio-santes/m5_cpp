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

#include "test_Common.hpp"

#include "PktDisconnect.hpp"
#include "PktAuth.hpp"

#include <cstring>

int test(void)
{
	m5::ReasonCode rc = m5::ReasonCode::CONTINUE_AUTHENTICATION;
	const char str[] = "Hello, World!";
	m5::AppBuf buf(128);
	m5::PktAuth *auth;

	auth = new m5::PktAuth();
	auth->reasonCode(rc);
	auth->authenticationMethod(str);
	auth->authenticationData((const uint8_t *)str, strlen(str));
	auth->userProperty(str, str);

	auth->writeTo(buf);

	m5::PktAuth authRead(buf);

	if (auth->reasonCode() != authRead.reasonCode()) {
		throw std::logic_error("read: Reason Code");
	}

	delete auth;

	return 0;
}

int testDisconnect(void)
{
	m5::ReasonCode rc = m5::ReasonCode::SERVER_MOVED;
	const char str[] = "Hello, World!";
	uint32_t u32 = 0x01ABCDEF;
	m5::AppBuf buf(128);
	m5::PktDisconnect *disconnect;

	disconnect = new m5::PktDisconnect();
	disconnect->reasonCode(rc);
	disconnect->sessionExpiryInterval(u32);
	disconnect->reasonString(str);
	disconnect->serverReference(str);
	disconnect->userProperty(str, str);

	disconnect->writeTo(buf);

	m5::PktDisconnect disconnectRead(buf);

	if (disconnect->reasonCode() != disconnectRead.reasonCode()) {
		throw std::logic_error("read: Reason Code");
	}

	delete disconnect;

	return 0;
}

int main(void)
{
	int rc;

	rc = test();
	test_rc(rc, "PktAuth");

	rc = testDisconnect();
	test_rc(rc, "PktDisconnect");

	return 0;
}

