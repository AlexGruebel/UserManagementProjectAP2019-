package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.UserSecurityEntity;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserSecurityRepository extends JpaRepository<UserSecurityEntity, Integer>{

    UserSecurityEntity findByUserName(String userName);
    
}