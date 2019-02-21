package com.ap.usermanagementproject.entities;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name="permissions")
public class Permission{
    @Id
    @Column(name="permissionid")
    private int id;
    @Column(name="upermissionname")
    private String permissionName;
    private String permission;

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the permissionName
     */
    public String getPermissionName() {
        return permissionName;
    }

    /**
     * @param permissionName the permissionName to set
     */
    public void setPermissionName(String permissionName) {
        this.permissionName = permissionName;
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

    
}