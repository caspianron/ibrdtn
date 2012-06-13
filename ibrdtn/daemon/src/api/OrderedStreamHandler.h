/*
 * OrderedStreamHandler.h
 *
 *   Copyright 2011 Johannes Morgenroth
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#ifndef ORDEREDSTREAMHANDLER_H_
#define ORDEREDSTREAMHANDLER_H_

#include "api/Registration.h"
#include "api/ClientHandler.h"
#include "api/BundleStreamBuf.h"

#include <iostream>

namespace dtn
{
	namespace api
	{
		class OrderedStreamHandler : public ProtocolHandler, public BundleStreamBufCallback
		{
		public:
			OrderedStreamHandler(ClientHandler &client, ibrcommon::tcpstream &stream);
			virtual ~OrderedStreamHandler();

			virtual void run();
			virtual void finally();
			virtual void __cancellation();

			virtual void put(dtn::data::Bundle &b);
			virtual dtn::data::MetaBundle get(size_t timeout = 0);
			virtual void delivered(const dtn::data::MetaBundle &m);

		private:
			class Sender : public ibrcommon::JoinableThread
			{
			public:
				Sender(OrderedStreamHandler &conn);
				virtual ~Sender();

			protected:
				void run();
				void finally();
				void __cancellation();

			private:
				OrderedStreamHandler &_handler;
			} _sender;

			BundleStreamBuf _streambuf;
			std::iostream _bundlestream;

			dtn::data::EID _peer;
			dtn::data::EID _endpoint;
			bool _group;
			size_t _lifetime;
		};
	} /* namespace api */
} /* namespace dtn */
#endif /* ORDEREDSTREAMHANDLER_H_ */
