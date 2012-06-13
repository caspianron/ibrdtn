/*
 * DiscoveryService.h
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

#ifndef DISCOVERYSERVICE_H_
#define DISCOVERYSERVICE_H_

#include <net/DiscoveryServiceProvider.h>
#include <ibrcommon/net/vinterface.h>
#include <stdlib.h>
#include <iostream>

namespace dtn
{
	namespace net
	{
		class DiscoveryService
		{
		public:
			DiscoveryService();
			DiscoveryService(DiscoveryServiceProvider *provider);
			DiscoveryService(std::string name, std::string parameters);
			virtual ~DiscoveryService();

			size_t getLength() const;

			std::string getName() const;
			std::string getParameters() const;

			/**
			 * updates the values of the service block
			 */
			void update(const ibrcommon::vinterface &net);

		protected:
			std::string _service_name;
			std::string _service_parameters;
			DiscoveryServiceProvider *_provider;

		private:
			friend std::ostream &operator<<(std::ostream &stream, const DiscoveryService &service);
			friend std::istream &operator>>(std::istream &stream, DiscoveryService &service);
		};
	}
}

#endif /* DISCOVERYSERVICE_H_ */
