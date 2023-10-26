/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <iostream>

#include "person.pb.h"

int main(int argc, char **argv)
{
  // initialize eCAL API
  eCAL::Initialize(argc, argv, "person subscriber");

  std::cout << std::endl << "FIRST RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    eCAL::protobuf::CSubscriber<pb::People::Person> sub("person");
    sub.AddReceiveCallback([](const char* /*topic_*/, const pb::People::Person& person_, long long /*time_*/, long long /*clock_*/, long long /*id_*/){std::cout << "person id : " << person_.id() << std::endl;});
    eCAL::Process::SleepMS(3000);
  }

  std::cout << std::endl << "SECOND RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    eCAL::protobuf::CSubscriber<pb::People::Person> sub("person");
    sub.AddReceiveCallback([](const char* /*topic_*/, const pb::People::Person& person_, long long /*time_*/, long long /*clock_*/, long long /*id_*/){std::cout << "person id : " << person_.id() << std::endl;});
    eCAL::Process::SleepMS(3000);
  }

  // finalize eCAL API
  eCAL::Finalize();

  // initialize eCAL API
  eCAL::Initialize(argc, argv, "person subscriber");

  std::cout << std::endl << "THIRD RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    eCAL::protobuf::CSubscriber<pb::People::Person> sub("person");
    sub.AddReceiveCallback([](const char* /*topic_*/, const pb::People::Person& person_, long long /*time_*/, long long /*clock_*/, long long /*id_*/){std::cout << "person id : " << person_.id() << std::endl;});
    eCAL::Process::SleepMS(3000);
  }

  std::cout << std::endl << "FOURTH RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    eCAL::protobuf::CSubscriber<pb::People::Person> sub1("person");
    sub1.AddReceiveCallback([](const char* /*topic_*/, const pb::People::Person& person_, long long /*time_*/, long long /*clock_*/, long long /*id_*/){std::cout << "sub1: person id : " << person_.id() << std::endl;});
    eCAL::protobuf::CSubscriber<pb::People::Person> sub2("person");
    sub2.AddReceiveCallback([](const char* /*topic_*/, const pb::People::Person& person_, long long /*time_*/, long long /*clock_*/, long long /*id_*/){std::cout << "sub2: person id : " << person_.id() << std::endl;});
    eCAL::Process::SleepMS(3000);

    std::cout << std::endl << "sub1.Destroy()" << std::endl;
    sub1.Destroy();
    eCAL::Process::SleepMS(3000);
  }

  // finalize eCAL API
  eCAL::Finalize();

  return(0);
}