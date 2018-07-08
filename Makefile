#
#                                   1byt3
#
#                              License Notice
#
# 1byt3 provides a commercial license agreement for this software. This
# commercial license can be used for development of proprietary/commercial
# software. Under this commercial license you do not need to comply with the
# terms of the GNU Affero General Public License, either version 3 of the
# License, or (at your option) any later version.
#
# If you don't receive a commercial license from us (1byt3), you MUST assume
# that this software is distributed under the GNU Affero General Public
# License, either version 3 of the License, or (at your option) any later
# version.
#
# Contact us for additional information: customers at 1byt3.com
#
#                          End of License Notice
#

#
# MQTT 5 Low Level Packet Library
#
# Copyright (C) 2017, 2018 1byt3, customers at 1byt3.com
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CXXFLAGS =		\
	-std=c++11	\
	-Wall		\
	-Wextra		\
	-Werror

INC =			\
	-Isrc		\
	-Iinclude	\
	-Itests

EXTRAFLAGS = -O0 -g

CXX ?= g++

SRCS_DIR = src

OBJS_DIR = obj

BINS_DIR = bin

INCS_DIR = include

TESTS_DIR = tests

VERSION = 0.0.1

LIB = lib/libm5++_$(VERSION).a

OBJS =				\
	obj/AppBuf.o		\
	obj/Packet.o		\
	obj/PktAuth.o		\
	obj/PktConnAck.o	\
	obj/PktConnect.o	\
	obj/PktDisconnect.o	\
	obj/PktPing.o		\
	obj/PktPubAck.o		\
	obj/PktPubComp.o	\
	obj/PktPublish.o	\
	obj/PktPubMsg.o		\
	obj/PktPubRec.o		\
	obj/PktPubRel.o		\
	obj/PktRCodeProp.o	\
	obj/PktSubAck.o		\
	obj/PktSubAckMsg.o	\
	obj/PktSubscribe.o	\
	obj/PktUnsubAck.o	\
	obj/PktUnsubscribe.o	\
	obj/Properties.o

TESTS =					\
	$(BINS_DIR)/test_AppBuf		\
	$(BINS_DIR)/test_Properties	\
	$(BINS_DIR)/test_PktConnect	\
	$(BINS_DIR)/test_PktConnAck	\
	$(BINS_DIR)/test_PktPublish	\
	$(BINS_DIR)/test_PktPubMsg	\
	$(BINS_DIR)/test_PktRCodeProp	\
	$(BINS_DIR)/test_PktPing	\
	$(BINS_DIR)/test_PktSubscribe	\
	$(BINS_DIR)/test_PktSubAckMsg	\
	$(BINS_DIR)/test_PktUnsubscribe

VALGRIND = valgrind -q --leak-check=full --error-exitcode=1

all: dirs $(LIB) $(TESTS)

dirs:
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p lib

$(LIB): $(OBJS)
	ar r $@ $^
	ranlib $@

$(OBJS_DIR)/%.o:			\
	$(SRCS_DIR)/%.cpp		\
	$(INCS_DIR)/%.hpp		\
	$(INCS_DIR)/Common.hpp
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) $(INC) -c -o $@ $<

$(OBJS_DIR)/test_%.o:			\
	$(TESTS_DIR)/test_%.cpp		\
	$(TESTS_DIR)/test_Common.hpp
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) $(INC) -c -o $@ $<

$(BINS_DIR)/test_%:			\
	$(OBJS_DIR)/test_%.o		\
	$(LIB)
	$(CXX) -o $@ $^

tests: $(TESTS)
	@$(foreach test, $(TESTS), ./$(test) || exit 1;)

memtest: $(TESTS)
	@$(foreach test, $(TESTS), $(VALGRIND) ./$(test) || exit 1;)

clean:
	rm -rf obj bin lib

.PHONY: all dirs tests memtest clean
