/*
 * (c) 2010 Alexander Warg <warg@os.inf.tu-dresden.de>
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 */
#pragma once

#include <l4/cxx/avl_set>
#include <l4/cxx/ipc_server>
#include <l4/cxx/hlist>

#include <l4/vbus/vbus_types.h>

#include "vdevice.h"
#include "device.h"

namespace Vi {
class Sw_icu;

class System_bus : public Device, public Dev_feature, public L4::Server_object
{
public:
  class Root_resource_factory : public cxx::H_list_item
  {
  public:
    virtual Root_resource *create(System_bus *bus) const = 0;
    Root_resource_factory()
    { _factories.push_front(this); }

    typedef cxx::H_list<Root_resource_factory> Factory_list;
    static Factory_list _factories;
  };

  template< unsigned TYPE, typename RS >
  class Root_resource_factory_t : public Root_resource_factory
  {
  public:
    Root_resource *create(System_bus *bus) const
    {
      return new Root_resource(TYPE, new RS(bus));
    }
  };

  System_bus();
  ~System_bus();

  // dispatch for the server object
  int dispatch(l4_umword_t obj, L4::Ipc::Iostream &ios);
  int dispatch(l4_umword_t, l4_uint32_t func, L4::Ipc::Iostream &ios);
  bool match_hw_feature(Hw::Dev_feature const *) const { return false; }

private:
  int request_resource(L4::Ipc::Iostream &ios);
  int request_iomem(L4::Ipc::Iostream &ios);

public:
  bool resource_allocated(Resource const *) const;

  void dump_resources() const;

private:
  struct Res_cmp
  {
    bool operator () (Resource const *a, Resource const *b) const
    {
      if (a->type() == b->type())
        return a->lt_compare(b);
      return a->type() < b->type();
    }
  };
  //typedef std::set<Resource*, Res_cmp> Resource_set;

public:
  typedef cxx::Avl_set<Resource*, Res_cmp> Resource_set;

  Resource_set const *resource_set() const { return &_resources; }
  Resource_set *resource_set() { return &_resources; }

  void set_host(Device *d) { _host = d; }
  Device *host() const { return _host; }
  Sw_icu *sw_icu() const { return _sw_icu; }

  void sw_icu(Sw_icu *icu) { _sw_icu = icu; }

private:
  Resource_set _resources;
  Device *_host;
  Sw_icu *_sw_icu;

};

}
