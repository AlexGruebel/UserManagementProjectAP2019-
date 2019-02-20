package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.User;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Integer>{
    
}