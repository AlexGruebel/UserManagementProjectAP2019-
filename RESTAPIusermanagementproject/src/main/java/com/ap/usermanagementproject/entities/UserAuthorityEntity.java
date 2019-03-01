package com.ap.usermanagementproject.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

import org.hibernate.annotations.Immutable;
import org.springframework.security.core.GrantedAuthority;

@Entity
@Immutable
@Table(name="users_permissions")
public class UserAuthorityEntity implements IEntity, GrantedAuthority{
    @Id
    private int id;
    private int userid;
    private String permission;

    /**
     * @return the uid
     */
    public int getUid() {
        return id;
    }

    /**
     * @param uid the uid to set
     */
    public void setUid(int uid) {
        this.id = uid;
    }

    /**
     * @return the userid
     */
    public int getUserId() {
        return userid;
    }

    /**
     * @param userid the userid to set
     */
    public void setUserId(int userid) {
        this.userid = userid;
    }

    public IEntity merge(IEntity entity){
        return this;
    }

    @Override
    public String getAuthority() {
        return permission;
    }

    public void setAuthority(String permission){
        this.permission = permission;
    }
}