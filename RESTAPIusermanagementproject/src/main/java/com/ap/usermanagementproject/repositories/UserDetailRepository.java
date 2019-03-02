package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.UserDetailEntity;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserDetailRepository extends JpaRepository<UserDetailEntity, Integer> {
    UserDetailEntity findByUserName(String userName);
}