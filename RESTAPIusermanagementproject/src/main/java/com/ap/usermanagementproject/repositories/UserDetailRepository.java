package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.UserDetail;

import org.springframework.data.jpa.repository.JpaRepository;

public interface UserDetailRepository extends JpaRepository<UserDetail, Integer> {

}