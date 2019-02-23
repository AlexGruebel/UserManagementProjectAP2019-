package com.ap.usermanagementproject.services;

import java.util.Optional;

import com.ap.usermanagementproject.entities.IEntity;

import org.springframework.data.jpa.repository.JpaRepository;

public abstract class BaseCRUDService<T extends IEntity, R extends JpaRepository<T, Integer>> extends BaseRService<T, R> {

    public T saveEntity(T entity){
        return super.getRepository().save(entity);
    }

    public T updateEntity(T entity, int id) throws Exception {
        Optional<T> optOld = super.getRepository().findById(id);
        T old =optOld.orElse(null);
        T rEntity = null; 
        if(old != null){  
            rEntity = (T) old.merge(entity);
            super.getRepository().save(rEntity);
        }else{
            new Exception("this entity does not exist you cant update an non exesting entity");
        }
        return rEntity;
    }

    public Optional<T> getEntityById(int id){
        return super.getRepository().findById(id);
    }

    public void deleteEntityById(int id){
        super.getRepository().deleteById(id);
    }
}