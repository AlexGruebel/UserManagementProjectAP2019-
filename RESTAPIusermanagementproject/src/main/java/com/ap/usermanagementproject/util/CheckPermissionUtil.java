package com.ap.usermanagementproject.util;

import java.security.AccessControlException;
import java.util.Collection;
import java.util.Optional;

import org.springframework.security.access.AccessDeniedException;
import org.springframework.security.core.GrantedAuthority;

public class CheckPermissionUtil {

    private CheckPermissionUtil(){}

    /*
    0 => read
    1 => modify (no arrays)
    2 => modify all
    */
    public static void checkPermission(String uri, Collection<GrantedAuthority> permissions) throws AccessDeniedException {
        Optional<GrantedAuthority> first = permissions.stream().filter(e-> uri.startsWith(e.getAuthority())).findFirst();
        if (!first.isPresent()){
            throw new AccessDeniedException("you dont have the necessary permission");
        }
    }
}