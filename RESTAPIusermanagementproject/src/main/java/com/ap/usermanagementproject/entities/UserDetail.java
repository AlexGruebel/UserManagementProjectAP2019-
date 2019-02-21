package com.ap.usermanagementproject.entities;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

@Entity
@Table(name = "users")
public class UserDetail extends BaseUser {

    private String pwhash;
    private String mail;

    @ManyToMany
    @JoinTable(name = "user_group_mapping"
              ,joinColumns = @JoinColumn(name = "userid")
              ,inverseJoinColumns = @JoinColumn(name = "groupid"))
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
}