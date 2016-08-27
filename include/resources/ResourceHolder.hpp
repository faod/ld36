#pragma once

#include <string>
#include <map>
#include <memory>

namespace faod
{
    /* Generic class that intend to hold a collection of heavyweight assets of the same type
     *  such as sounds, textures...
     */


    template <typename Resource, typename Ident>
    class ResourceHolder
    {
        public:
            //Resource class is heavyweight: copying it is nonsense
            ResourceHolder(const ResourceHolder& c) 		   = delete;
            ResourceHolder(ResourceHolder&& c)      		   = delete;
            ResourceHolder& operator=(const ResourceHolder& c) = delete;
            ResourceHolder& operator=(ResourceHolder&& c)      = delete;
			
            //Only constructor : an empty collection
            ResourceHolder() {}
			
            /** Load the resource with "filename" and assiociate it with id in the collection
             *  Resource type is expected to have a method loadFromFile(string) that returns a boolean
             *  true if successfully loaded, false otherwise
             *  throw std::runtime_error exception if failure to load
             */
            void load(Ident id, const std::string& filename);
			
            /** Same as load(Ident, const std::string&)
             *  except that Resource type is expected to have a method loadFromFile(string, param)
             */
            template <typename Parameter>
            void load(Ident id, const std::string& filename, const Parameter& param);

            /*
             *  Release a resource
             */
            void release(Ident id);

            //Returns a reference to a Resource having the Id id
            Resource& 		get(Ident id);
            const Resource& get(Ident id) const;


        private:
            //helper function to add an item into the collection
            void insertResource(Ident id, std::unique_ptr<Resource> resource);


            std::map<Ident, std::unique_ptr<Resource>> resources_;
    };

}

#include "ResourceHolder.inl"
