package com.ap.usermanagementproject.services;

import java.util.Set;

import com.ap.usermanagementproject.entities.GroupEntity;
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
        //entity to save have to be cloned becouse Hibernate throws an Exception if you try to insert an casted object
        UserDetail entityToSave = (UserDetail) entity.clone();
        return super.saveEntity(entityToSave);
    }

    @Override 
    public UserDetail updateEntity(UserDetail entity, int id) throws Exception{
        entity = castEntityAndSetPW(entity);
        return super.updateEntity(entity, id);
    }
    /**
     * casts an UserDetailEntity to an UserDetailWithPWEntity to access the pw field and 
     * generates a new hash value for the user if the pw field is not null
     * @param UserDetailEntity
     * @return the same UserDetailEntity maybe with a new filled pwhash 
     */
    private UserDetail castEntityAndSetPW(UserDetail entity){
        //only extrat the PW if it exists, becouse the user is able to update informations without sending a pw in the json  
        String pw = ((UserDetailWithPWEntity) entity).getPassword();
        if(pw != null){
            entity.setPwhash(encoder.encode(pw)); 
        }
        return entity;
    }

    /**
     * searches for an User by his username
     * @param userName UserName
     * @return UserDetail 
     */
    public UserDetail findEntityByName(String userName){
        return super.getRepository().findByUserName(userName);
    }
    /**
     * checks if the user is an admin
     * @param userName 
     * @return a boolean is the given user an admin
     */
    public boolean isAdmin(String userName){
        Set<GroupEntity> groups = this.findEntityByName(userName).getGroups();
        return groups.stream().filter(e -> e.getGroupname().equals("admin")).findFirst().isPresent();
    }
}