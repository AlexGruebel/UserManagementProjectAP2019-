package com.ap.usermanagementproject.entities;

import javax.persistence.Entity;
import javax.persistence.MappedSuperclass;
import javax.persistence.Table;
import javax.persistence.Transient;

import com.fasterxml.jackson.annotation.JsonIgnore;

public class UserDetailWithPWEntity extends UserDetail {
    @Transient
    private String password;

    /**
     * @return the password
     */
    
    public String getPassword() {
        return password;
    }

    /**
     * @param password the password to set
     */
    public void setPassword(String password) {
        this.password = password;
    }    
}