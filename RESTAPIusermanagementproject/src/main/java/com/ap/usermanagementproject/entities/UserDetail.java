package com.ap.usermanagementproject.entities;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

import com.fasterxml.jackson.annotation.JsonIgnore;
@Entity
@Table(name = "users")
public class UserDetail extends BaseUser {
    @JsonIgnore
    private String pwhash;
    private String mail;

    @ManyToMany
    @JoinTable(name = "user_group_mapping", joinColumns = @JoinColumn(name = "userid"), inverseJoinColumns = @JoinColumn(name = "groupid"))
    private Set<Group> groups = new HashSet<Group>();

    /**
     * @return the pwhash
     */
    public String getPwhash() {
        return pwhash;
    }

    /**
     * @param pwhash the pwhash to set
     */
    public void setPwhash(String pwhash) {
        this.pwhash = pwhash;
    }

    /**
     * @return the mail
     */
    public String getMail() {
        return mail;
    }
    /**
     * @param mail the mail to set
     */
    public void setMail(String mail) {
        this.mail = mail;
    }

    /**
     * @param groups the groups to set
     */
    public void setGroups(Set<Group> groups) {
        this.groups = groups;
    }

    /**
     * @return the groups
     */
    public Set<Group> getGroups() {
        return groups;
    }

    @Override
    public Object clone(){
        UserDetail clone = new UserDetail();
        clone.setId(getId());
        clone.setUserName(getUserName());
        clone.setMail(getMail());
        clone.setPwhash(getPwhash());
        clone.setGroups(getGroups());
        return clone;
    }

    @Override
    public IEntity merge(IEntity entity){
        UserDetail nUserDetail = (UserDetail) entity;

        if(nUserDetail.getGroups().size() != 0){
            this.setGroups(nUserDetail.getGroups());
        }

        if(nUserDetail.getMail() != null){
            this.setMail(nUserDetail.getMail());
        }

        if(nUserDetail.getPwhash() != null){
            this.setPwhash(nUserDetail.getPwhash());
        }
        return this;
    }
}