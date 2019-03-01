package com.ap.usermanagementproject.services;

import java.util.Optional;

import com.ap.usermanagementproject.entities.IEntity;

import org.springframework.data.jpa.repository.JpaRepository;

public abstract class BaseCRUDService<T extends IEntity, R extends JpaRepository<T, Integer>> extends BaseRService<T, R> {

    /**
     * @param entity to save
     */
    public T saveEntity(T entity){
        return super.getRepository().save(entity);
    }

    /**
     * updates the Entity in the database, only attributes that are not null will be updated
     * @param entity to update
     * @param id of the entity to update
     * @return updated Entity
     */
    public T updateEntity(T entity, int id) throws Exception {
        Optional<T> optOld = super.getRepository().findById(id);
        T old = optOld.orElse(null);
        T rEntity = null; 
        //only save the Entity if there were any updates 
        if(old != null){  
            //merge the new entity to the existing one, so the rest client only have to send only the updated fields
            rEntity = (T) old.merge(entity);
            super.getRepository().save(rEntity);
        }else{
            new Exception("this entity does not exist you cant update an non exesting entity");
        }
        return rEntity;
    }
    /**
     * searches for an specific Entity by id in the given repository
     * @param id of the Entity
     * @return Entity if it exists 
     */
    public Optional<T> getEntityById(int id){
        return super.getRepository().findById(id);
    }
    /**
     * deletes an specific Entity by id in the given repository
     * @param id of the Entity
     */
    public void deleteEntityById(int id){
        super.getRepository().deleteById(id);
    }
}