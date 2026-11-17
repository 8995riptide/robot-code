import type * as React from 'react';

declare module 'react' {
  namespace JSX {
    interface IntrinsicElements {
      'model-viewer': React.DetailedHTMLProps<
      React.HTMLAttributes<HTMLElement> & {
        src?: string;
        alt?: string;
        poster?: string;
        'auto-rotate'?: boolean;
        'camera-controls'?: boolean;
        ar?: boolean;
        'ar-modes'?: string;
        'environment-image'?: string;
        exposure?: number;
        'shadow-intensity'?: number;
        'shadow-softness'?: number;
        'skybox-image'?: string;
        'staging-environment-image'?: string;
        loading?: 'eager' | 'lazy';
        'draco-decoder-location'?: string;
        'meshopt-decoder-location'?: string;
      },
      HTMLElement
      >;
    }
  }
}