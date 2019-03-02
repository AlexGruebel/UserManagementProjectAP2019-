package com.ap.usermanagementproject.repositories;
import com.ap.usermanagementproject.entities.PermissionEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PermissionRepository extends JpaRepository<PermissionEntity, Integer> {}