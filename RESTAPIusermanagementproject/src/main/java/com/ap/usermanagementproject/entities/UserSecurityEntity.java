package com.ap.usermanagementproject.entities;

import java.util.List;
import java.util.Set;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.JoinColumn;
import javax.persistence.JoinColumns;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Transient;

import org.hibernate.annotations.ForeignKey;
import org.springframework.data.jpa.repository.Query;
@Entity
@Table(name="users")
public class UserSecurityEntity extends BaseUser{

    private String pwhash;

    //this does not work, I currently do not unterstand why? I temp fixed it in the UMUserDetailService, 
    //where I incheck the permission
    //@OneToMany()
    //@JoinColumn(name = "userid")
    @Transient
    private Set<UserAuthorityEntity> permissions;

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
     * @return the userPermissions
     */
    public Set<UserAuthorityEntity> getUserPermissions() {
        return permissions;
    }

    /**
     * @param userPermissions the userPermissions to set
     */
    public void setUserPermissions(Set<UserAuthorityEntity> userAuthoritys) {
        this.permissions= userAuthoritys;
    }
    

    @Override
    public IEntity merge(IEntity old) {
        return null;
    }

    
}