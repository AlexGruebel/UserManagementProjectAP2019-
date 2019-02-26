package com.ap.usermanagementproject.services;

import java.util.Set;

import com.ap.usermanagementproject.entities.Group;
import com.ap.usermanagementproject.entities.IEntity;
import com.ap.usermanagementproject.entities.UserDetail;
import com.ap.usermanagementproject.entities.UserDetailWithPWEntity;
import com.ap.usermanagementproject.repositories.UserDetailRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class UserDetailCRUDService extends BaseCRUDService<UserDetail, UserDetailRepository> {

    private PasswordEncoder encoder;

    @Autowired
    public void setPasswordEncoder(PasswordEncoder encoder){
        this.encoder = encoder;
    }

    @Override
    public UserDetail saveEntity(UserDetail entity){
        entity = castEntityAndSetPW(entity);
        UserDetail entityToSave = (UserDetail) entity.clone();
        return super.saveEntity(entityToSave);
    }

    @Override 
    public UserDetail updateEntity(UserDetail entity, int id) throws Exception{
        entity = castEntityAndSetPW(entity);
        return super.updateEntity(entity, id);
    }

    private UserDetail castEntityAndSetPW(UserDetail entity){
        String pw = ((UserDetailWithPWEntity) entity).getPassword();
        if(pw != null){
            entity.setPwhash(encoder.encode(pw)); 
        }
        return entity;
    }

    public UserDetail findEntityByName(String name){
        return super.getRepository().findByUserName(name);
    }

    public boolean isAdmin(String username){
        Set<Group> groups = this.findEntityByName(username).getGroups();
        System.out.println(groups.toArray()[0]);
        return groups.stream().filter(e -> e.getGroupname().equals("admin")).findFirst().isPresent();
    }
}