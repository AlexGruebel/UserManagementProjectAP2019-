package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.UserEntity;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<UserEntity, Integer>{

    UserEntity findByUserName(String userName);
    
}