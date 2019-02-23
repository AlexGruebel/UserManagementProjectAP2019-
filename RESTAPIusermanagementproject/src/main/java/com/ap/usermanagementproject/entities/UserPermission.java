package com.ap.usermanagementproject.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

import org.hibernate.annotations.Immutable;

@Entity
@Immutable
@Table(name="user_permissions")
public class UserPermission implements IEntity{
    @Id
    private int uid;
    @Column(name="userId")
    private int userId;
    private String permission;

    /**
     * @return the uid
     */
    public int getUid() {
        return uid;
    }

    /**
     * @param uid the uid to set
     */
    public void setUid(int uid) {
        this.uid = uid;
    }

    /**
     * @return the userid
     */
    public int getUserId() {
        return userId;
    }

    /**
     * @param userid the userid to set
     */
    public void setUserId(int userid) {
        this.userId = userid;
    }

    /**
     * @return the permission
     */
    public String getPermission() {
        return permission;
    }

    /**
     * @param permission the permission to set
     */
    public void setPermission(String permission) {
        this.permission = permission;
    }

    public IEntity merge(IEntity entity){
        return this;
    }
}