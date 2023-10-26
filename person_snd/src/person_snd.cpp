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
#include <ecal/msg/protobuf/publisher.h>

#include <iostream>

#include "person.pb.h"

int main(int argc, char **argv)
{
  // initialize eCAL API
  eCAL::Initialize(argc, argv, "person publisher");

  // generate a class instance of Person
  pb::People::Person person;
  person.set_name("Max");

  auto cnt = 0;

  std::cout << std::endl << "FIRST RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    person.set_name("FIRST RUN");
    eCAL::protobuf::CPublisher<pb::People::Person> pub("person");
    while (cnt < 10)
    {
      person.set_id(++cnt);
      pub.Send(person);
      eCAL::Process::SleepMS(500);
    }
  }

  std::cout << std::endl << "SECOND RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    person.set_name("SECOND RUN");
    eCAL::protobuf::CPublisher<pb::People::Person> pub("person");
    while (cnt < 20)
    {
      person.set_id(++cnt);
      pub.Send(person);
      eCAL::Process::SleepMS(500);
    }
  }

  // finalize eCAL API
  eCAL::Finalize();

  // initialize eCAL API
  eCAL::Initialize(argc, argv, "person publisher");

  std::cout << std::endl << "THIRD RUN" << std::endl << std::endl; eCAL::Process::SleepMS(1000);
  {
    person.set_name("THIRD RUN");
    eCAL::protobuf::CPublisher<pb::People::Person> pub("person");
    while (cnt < 30)
    {
      person.set_id(++cnt);
      pub.Send(person);
      eCAL::Process::SleepMS(500);
    }
  }

  // finalize eCAL API
  eCAL::Finalize();

  return(0);
}
